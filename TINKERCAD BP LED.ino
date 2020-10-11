/*
  Bouton poussoir + LED / TINKERCAD

  by Philippe MARTIN

  modified Oct 2020

  This example code is in the public domain
*/

const int LED_OUTPUT = 13;  // Constante qui détermine le numéro de pin utilisé
const int BP_INPUT = 7; // Constante qui détermine le numéro de pin utilisé

int etatBouton = 0; // On initialise une variable pour le bouton poussoir

void setup() {
pinMode(LED_OUTPUT, OUTPUT); // On positionne le pin en sortie
pinMode(BP_INPUT, INPUT_PULLUP); // On positionne le pin en sortie
Serial.begin(9600);
}

void loop() {
  // Lecture de l'état du bouton poussoir
  etatBouton = digitalRead(BP_INPUT);
  Serial.print("Etat du bouton : ");
  Serial.println(etatBouton);

  if (etatBouton == LOW) {
    // turn LED on:
    digitalWrite(LED_OUTPUT, HIGH);
  } else {
    // turn LED off:
    digitalWrite(LED_OUTPUT, LOW);
  }
}
