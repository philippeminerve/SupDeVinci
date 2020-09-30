/*
  Bouton poussoir + LED

  by Philippe MARTIN
  modified Sep 2020

  This example code is in the public domain

*/
const int LED_OUTPUT = 2;  // Constante qui détermine le numéro de pin utilisé
const int BP_INPUT = 8; // Constante qui détermine le numéro de pin utilisé

int etatBouton = 0; // On initialise une variable pour le bouton poussoir

void setup() {
pinMode(LED_OUTPUT, OUTPUT); // On positionne le pin en sortie
pinMode(BP_INPUT, INPUT); // On positionne le pin en sortie
Serial.begin(9600);
}
 
void loop() {
  // Lecture de l'état du bouton poussoir
  etatBouton = digitalRead(BP_INPUT);
  Serial.print("Etat du bouton : ");
  Serial.println(etatBouton);

  if (etatBouton == HIGH) {
    // turn LED on:
    digitalWrite(LED_OUTPUT, HIGH);
  } else {
    // turn LED off:
    digitalWrite(LED_OUTPUT, LOW);
  }
}
