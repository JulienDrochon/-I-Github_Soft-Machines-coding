//Déclaration de variables constantes
#define PIN_LED_STRIP_01 9// pin arduino où est raccordé la première led strip = pin 9

// déclaration variables
int vitesse = 1000; // 1000 millisecondes = 1 seconde

void setup() {
  //déclaration de la pin numérique 9 en tant que sortie
  pinMode(PIN_LED_STRIP_01, OUTPUT);
}


void loop() {
  analogWrite(PIN_LED_STRIP_01, 255);
  delay(vitesse);
  analogWrite(PIN_LED_STRIP_01, 0);
  delay(vitesse);
}
