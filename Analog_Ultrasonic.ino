/*
  Capteur ultrasonic US-016
  by Philippe MARTIN
  modified Sep 2020
  This example code is in the public domain
*/

int ADCValue;
void setup(){
    Serial.begin(9600);
}
 
void loop(){
 
    ADCValue = analogRead(0);
    Serial.print("Distance : ");
    Serial.print(ADCValue, DEC);
    Serial.println("mm");
    delay(1000); //delay 1S
}
