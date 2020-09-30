/*
  Pilotage du drivers moteur MTX1508

  by Philippe MARTIN
  modified Sep 2020

  This example code is in the public domain
*/

const int PIN_AVANCE = 10; //Pin pour piloter la marche avant
const int PIN_RECULE = 9;  //Pin pour piloter la marche arrière

int duree_cycle = 3000; // Durée du cycle

int vitesse = 120; //Vitesse (0-255)

boolean estEnAvant = true; //Direction

void setup()
{
  pinMode(PIN_AVANCE, OUTPUT);
  pinMode(PIN_RECULE, OUTPUT);
}

void loop()
{
  if(estEnAvant)
  {
    analogWrite(PIN_AVANCE,vitesse); // Marche avant
    delay(duree_cycle);
    analogWrite(PIN_AVANCE,0); // Arrêt
    estEnAvant =! estEnAvant; // Inversion de la direction
    delay(20);
  }
  else
  {
    analogWrite(PIN_RECULE,vitesse);  
    delay(duree_cycle);
    analogWrite(PIN_RECULE,0);
    estEnAvant =! estEnAvant;
    delay(20);
  }
}
