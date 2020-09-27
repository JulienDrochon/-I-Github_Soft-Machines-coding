//Déclaration de variables constantes
#define PIN_LED_STRIP_01 9// pin arduino où est raccordé la première led strip = pin 9
#define PIN_LED_STRIP_02 10// pin arduino où est raccordé la deuxième led strip = pin 10
#define PIN_LED_STRIP_03 11// pin arduino où est raccordé la deuxième led strip = pin 11
//#define FADESPEED 7 // Vitesse

// déclaration variables
int vitesse = 1000; // 1000 millisecondes = 1 seconde


void setup() {
  //déclaration de la pin numérique 9 en tant que sortie
  pinMode(PIN_LED_STRIP_01, OUTPUT);
  //déclaration de la pin numérique 10 en tant que sortie
  pinMode(PIN_LED_STRIP_02, OUTPUT);
  //déclaration de la pin numérique 11 en tant que sortie
  pinMode(PIN_LED_STRIP_03, OUTPUT);
}


void loop() {
  analogWrite(PIN_LED_STRIP_01, 255);
  analogWrite(PIN_LED_STRIP_02, 255);
  analogWrite(PIN_LED_STRIP_03, 255);
  delay(vitesse);
  analogWrite(PIN_LED_STRIP_01, 0);
  analogWrite(PIN_LED_STRIP_02, 0);
  analogWrite(PIN_LED_STRIP_03, 0);
  delay(vitesse);
}
