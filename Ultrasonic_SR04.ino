/*
  Capteur ultrasonic HC-SR04

  by Philippe MARTIN
  modified Sep 2020

  This example code is in the public domain
*/

const byte TRIGGER_PIN = 2; // Broche TRIGGER
const byte ECHO_PIN = 3;    // Broche ECHO
 
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;
void setup() {
  Serial.begin(9600);
   
  /* Initialise les broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER est à 0 au repos
  pinMode(ECHO_PIN, INPUT);

}

void loop() {
  // Déclencher le trigger
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  // Mesure du délai de signal sur Echo
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
   
  // Calcul de la distance
  float distance_mm = measure / 2.0 * SOUND_SPEED;
   
  // Affichage du résultat
  Serial.print(F("Distance: "));
  Serial.print(distance_mm);
  Serial.print(F("mm ("));
  Serial.print(distance_mm / 10.0, 2);
  Serial.print(F("cm, "));
  Serial.print(distance_mm / 1000.0, 2);
  Serial.println(F("m)"));
   
  // frequence de rafraichissement
  delay(500);

}
