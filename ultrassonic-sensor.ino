#include <Servo.h>

const int triggerPin = A0;
const int echoPin = A1;

Servo servo_3;

float frente = 0;
float esquerda = 0;
float direita = 0;

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo_3.attach(3, 500, 2500);

  // Motor pins
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
}

long readUltrasonicDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // timeout 30000 us (30 ms) para evitar travar pulseIn
  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) {
    // timeout ocorreu, nada detectado
    return -1;
  }
  return duration;
}

float readDistanceCM(int triggerPin, int echoPin) {
  long duration = readUltrasonicDistance(triggerPin, echoPin);
  if (duration == -1) return -1; // nada detectado
  return duration / 58.0; // converte para cm
}

void loop() {
  delay(500);

  // Centraliza o servo
  servo_3.write(90);
  delay(300);

  frente = readDistanceCM(triggerPin, echoPin);
  if (frente == -1) {
    Serial.println("Sem leitura válida");
  } else {
    Serial.print("Distância à frente: ");
    Serial.print(frente);
    Serial.println(" cm");
  }
  delay(200);

  // Anda enquanto não tem obstáculo à frente
  while (frente > 30 || frente == -1) {  // permite andar se sem leitura
    frente = readDistanceCM(triggerPin, echoPin);
    Serial.print("FRENTE: ");
    if (frente == -1)
      Serial.println("Sem leitura");
    else
      Serial.println(frente);

    // Movimento para frente
    digitalWrite(7, LOW);  // Motor A - trás
    digitalWrite(6, HIGH); // Motor A - frente
    digitalWrite(5, HIGH);  // Motor B - trás
    digitalWrite(4, LOW); // Motor B - frente

    delay(200);
  }

  // Parar o carrinho
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  delay(300);

  // Escaneia para os lados
  servo_3.write(0);  // Olha para esquerda
  delay(500);
  direita = readDistanceCM(triggerPin, echoPin);
  Serial.print("direita: ");
  if (direita == -1) Serial.println("Sem leitura");
  else Serial.println(direita);

  servo_3.write(180);  // Olha para direita
  delay(500);
  esquerda = readDistanceCM(triggerPin, echoPin);
  Serial.print("esquerda: ");
  if (esquerda == -1) Serial.println("Sem leitura");
  else Serial.println(esquerda);

  // Decide para onde virar
  if (esquerda > direita) {
    // Virar à esquerda
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);  // Esquerdo frente
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);   // Direito trás
    delay(300);
  } 
  if (esquerda < direita) {
    // Virar à direita
    digitalWrite(7,HIGH);
    digitalWrite(6, LOW);   // Esquerdo frente
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);  // Direito frente
    delay(300);
  }

  // Parar e voltar a frente
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  delay(300);

  servo_3.write(90);  // Volta o servo para frente
  delay(300);
}