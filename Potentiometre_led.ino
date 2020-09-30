 // Initialise la variable qui va recueillir la valeur du potentiomètre
int potentiometre = 0; 

// Initialise la variable de la led
const int PIN_LED = 6;

// Initialise la variable qui permettra d'envoyer le bon rapport cyclique à la led
int lum_led = 0;

void setup() {
  Serial.begin(9600); //Initialise la communication entre le PC et Arduino
}

void loop() {
  // Lire la valeur du potentiomètre
  potentiometre = analogRead(A0); 

  //Affiche la valeur du potentiomètre sur le moniteur série
  Serial.println(potentiometre);  

  // Discrétise la valeur du potentiomètre et l'assigne à la valeur de la luminisoté de la LED
  lum_led = map(potentiometre, 0, 1023, 0, 255);   

  // Envoyer la valeur du potentiomètre à la led  
  analogWrite(PIN_LED,lum_led);              

  //Pause de 200 millisecondes
  delay(200); 
}
