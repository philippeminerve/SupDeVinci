/*
  Pilotage de moteur DC via L293D

  by Philippe MARTIN

  modified Oct 2020

  This example code is in the public domain

*/

int in1_moteur = 10; 
int in2_moteur = 7;
int pwm_moteur =11;
const int VITESSE_MOTEUR = 100; // 0-255

void setup() {
	pinMode(in1_moteur, OUTPUT); 
	pinMode(in2_moteur, OUTPUT);
	analogWrite(pwm_moteur,VITESSE_MOTEUR);
}
void loop() {
	// Le moteur tourne dans le sens normal
	digitalWrite(in1_moteur, HIGH);
	digitalWrite(in2_moteur, LOW);
	delay( 3000 );
	// Le moteur est à l'arrêt
digitalWrite(in1_moteur, LOW); 
digitalWrite(in2_moteur, LOW);
delay(500);
// Le moteur tourne dans le sens inverse
digitalWrite(in1_moteur, LOW);
digitalWrite(in2_moteur, HIGH);
delay( 3000 ); 
// Le moteur est à l'arrêt
digitalWrite(in1_moteur, LOW);
digitalWrite(in2_moteur, LOW);
delay(500);
}