/*
  Moteur pas à pas 28byj-48 avec driver ULN2003

  by Philippe MARTIN
  modified Sep 2020

  Pin 12  ==> IN1
  Pin 11  ==> IN2
  Pin 10   ==> IN3
  Pin 9   ==> IN4

  5V      ==> VCC+
  GND     ==> GND
  
  This example code is in the public domain

*/
// Arduino Stepper.h library:
#include <Stepper.h>

// Nombre de pas par rotation:
const int pasParRotation = 2048;

Stepper myStepper = Stepper(pasParRotation, 12, 10, 11, 9);

void setup() {
  // Vitesse en rpm : 5 à 10 rpm:
  myStepper.setSpeed(10);
  
  // Begin Serial communication at a baud rate of 9600:
  Serial.begin(9600);
}
void loop() {
  // Rotation en sens horaire:
  Serial.println("SansHoraire");
  myStepper.step(pasParRotation);
  delay(500);
  
  // Rotation sens anti horaire:
  Serial.println("AntiHoraire");
  myStepper.step(-pasParRotation);
  delay(500);
}
