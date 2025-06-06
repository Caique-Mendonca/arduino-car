
// C++ code
#include <SoftwareSerial.h>

// Definição dos pinos para comunicação com o módulo Bluetooth
int bluetoothTx = 9;  // Pino TX do módulo Bluetooth conectado ao RX do Arduino
int bluetoothRx = 8;  // Pino RX do módulo Bluetooth conectado ao TX do Arduino

// Inicialização do objeto para comunicação Bluetooth
SoftwareSerial bluetooth(bluetoothRx, bluetoothTx);
  // Pino RX do módulo Bluetooth conectado ao TX do Arduino
int item = 0;
// Inicialização do objeto para comunicação Bluetooth

void setup()
{
    // Inicialização da comunicação serial padrão (para comunicação com o computador via USB)
  // Inicialização da comunicação serial com o módulo Bluetooth
  bluetooth.begin(9600);
  // Motor Esquerdo
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop()
{
     if(bluetooth.available() > 0)
   {
	char direcao = bluetooth.read();
    // Condicional para Ligar o LED
    if (direcao == '1') {
    digitalWrite(13,HIGH);
    Serial.println('LIGADO');
    }
    // Condicional para Desligar o LED
    if (direcao == '0') {
    digitalWrite(13,LOW);
    Serial.println('DESLIGADO');
    }
    //frente
    if (direcao == 'w') {
      digitalWrite(7, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
    }
    //tras
    if (direcao == 's') {
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
    }
    //esquerda
    if(direcao == 'a'){
      digitalWrite(7, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
    }
    //direita
    if(direcao == 'd'){
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
    }
    //parado
    if(direcao == 'x'){
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
    }
  }
  delay(10);


  // //TRAS
  // digitalWrite(7, HIGH);
  // digitalWrite(6, LOW);
  // digitalWrite(5, LOW);
  // digitalWrite(4, HIGH);
  // delay(2000); // Wait for 2000 millisecond(s)
  // //FRENTE
  // digitalWrite(7, LOW);
  // digitalWrite(6, HIGH);
  // digitalWrite(5, HIGH);
  // digitalWrite(4, LOW);
  // delay(2000); // Wait for 2000 millisecond(s)
  // //PARADO
  // digitalWrite(7, LOW);
  // digitalWrite(6, LOW);
  // digitalWrite(5, LOW);
  // digitalWrite(4, LOW);
  // delay(2000); // Wait for 2000 millisecond(s)
  // //LADO
  // digitalWrite(7, LOW);
  // digitalWrite(6, HIGH);
  // digitalWrite(5, LOW);
  // digitalWrite(4, LOW);
  // delay(2000); // Wait for 2000 millisecond(s)
  // //LADO
  // digitalWrite(7, LOW);
  // digitalWrite(6, LOW);
  // digitalWrite(5, HIGH);
  // digitalWrite(4, LOW);
  // delay(2000); // Wait for 2000 millisecond(s)
}
