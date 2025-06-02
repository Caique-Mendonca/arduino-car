// C++ code
//
int Direita = 0;

int Esquerda = 0;

void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop()
{
  Serial.print(analogRead(A0));
Serial.print(',');
  Serial.println(analogRead(A1));
  if (analogRead(A0) > 200 && analogRead(A1) < 200) {
    analogWrite(3, 0);
    analogWrite(5, 145);
    analogWrite(6, 0);
    analogWrite(10, 0);
  }
  if (analogRead(A0) < 200 && analogRead(A1) > 200) {
    analogWrite(3, 0);
    analogWrite(5, 0);
    analogWrite(6, 145);
    analogWrite(10, 0);
  }
  if (analogRead(A0) < 200 && analogRead(A1) < 200) {
    analogWrite(3, 0);
    analogWrite(5, 145);
    analogWrite(6, 145);
    analogWrite(10, 0);
  } // Delay a little bit to improve simulation performance
  delay(10);
}