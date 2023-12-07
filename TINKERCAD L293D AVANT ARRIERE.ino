//
Pilotage de moteur DC via L293D

  by Philippe MARTIN

  modified Nov 2023

  This example code is in the public domain
//

const int controlPin1 = 2;
const int controlPin2 = 3;
const int enablePin = 9;
void setup()
{
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);
  
}

void loop()
{
  //forward
  digitalWrite(controlPin1, HIGH);
  digitalWrite(controlPin2, LOW);
  digitalWrite(enablePin, HIGH);
  delay(3000); // Wait for 3 s
  //stop
  digitalWrite(controlPin1, LOW);
  digitalWrite(controlPin2, LOW);
  digitalWrite(enablePin, LOW);
  delay(100); // Wait for 100 millisecond(s)
  //Reverse
  digitalWrite(controlPin1, LOW);
  digitalWrite(controlPin2, HIGH);
  digitalWrite(enablePin, HIGH);
  delay(3000); // Wait for 3 s
  //stop
  digitalWrite(controlPin1, LOW);
  digitalWrite(controlPin2, LOW);
  digitalWrite(enablePin, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}
