//Déclaration de variables constantes
#define PIN_LED_STRIP_01 9// pin arduino où est raccordé la première led strip = pin 9

// déclaration variables
int fondu01 = 0;
int vitesseFondu = 50;

void setup() {
  //déclaration de la pin numérique 9 en tant que sortie
  pinMode(PIN_LED_STRIP_01, OUTPUT);
}


void loop() {
  //fondu lumineux de la led strip#1 branchée sur le pin 9 de l'arduino
  if (fondu01 < 255) {
    fondu01 = fondu01 + 1;
    analogWrite(PIN_LED_STRIP_01, fondu01);
  } else {
    fondu01 = 0;
  }
  delay(vitesseFondu);
}
