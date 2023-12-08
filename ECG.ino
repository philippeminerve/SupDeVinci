/*
  ECG

  by Philippe MARTIN
  modified Dec 2023

  This example code is in the public domain

*/
void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT); // Setup for leads off detection LO +
  pinMode(9, INPUT); // Setup for leads off detection LO -
}

void loop() {
  if((digitalRead(8) == 1) || (digitalRead(9) == 1)){ //check if leads are removed
  Serial.println("leads off!");
}
else{
  Serial.println(analogRead(A0));
}
delay(1);
}
