//Déclaration de variables constantes
#define PIN_LED_STRIP_01 9// pin arduino où est raccordé la première led strip = pin 9

// déclaration variables
int fondu01 = 0;
int vitesseFondu = 10;
int fonduMontant01;

void setup() {
  //déclaration de la pin numérique 9 en tant que sortie
  pinMode(PIN_LED_STRIP_01, OUTPUT);
}


void loop() {
  //fondu lumineux de la led strip #1 branchée sur le pin 9 de l'arduino
  if ( fondu01 == 255) {
    fonduMontant01 = -1;
  }
  if (fondu01 == 0) {
    fonduMontant01 = 1;
  }
  fondu01 = fondu01 + fonduMontant01;

  analogWrite(PIN_LED_STRIP_01, fondu01);
  delay(vitesseFondu);
}
