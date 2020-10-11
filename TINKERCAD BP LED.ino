bool estPresse = 0;

void setup()
{
  pinMode(6, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  bool estPresse = 0;
  estPresse = digitalRead(6);
  Serial.println(estPresse);
  if (estPresse) 
  	{
  		digitalWrite(13, HIGH);
  	}
}