/*
  Blink LED adapté au pin 13

  by Philippe MARTIN
  modified Sep 2020

  This example code is in the public domain

*/
const int LED_OUTPUT = 13;  // Constante qui détermine le numéro de pin utilisé
const int DELAI_BLINK = 1000; // Constante du délai d'allumage extinction en ms

void setup() {
  pinMode(LED_OUTPUT, OUTPUT); // On positionne le pin en sortie
}
 
void loop() {
  digitalWrite(LED_OUTPUT, HIGH);   // LED allumée
  delay(DELAI_BLINK);               // Attendre
  digitalWrite(LED_OUTPUT, LOW);    // LED éteinte
  delay(DELAI_BLINK);               // Attendre
}
