//Déclaration de variables constantes
#define PIN_LED_STRIP_01 9// pin arduino où est raccordé la première led strip = pin 9
#define PIN_LED_STRIP_02 6// pin arduino où est raccordé la deuxième led strip = pin 6
//#define FADESPEED 7 // Vitesse

// déclaration variables
int fondu01 = 0;
int fondu02 = 255;
int vitesseFondus = 50;

void setup() {
  //déclaration de la pin numérique 9 en tant que sortie
  pinMode(PIN_LED_STRIP_01, OUTPUT);
  //déclaration de la pin numérique 6 en tant que sortie
  pinMode(PIN_LED_STRIP_02, OUTPUT);
}


void loop() {
  //fondu lumineux de la led strip #1 branchée sur le pin 9 de l'arduino
  if (fondu01 < 255) {
    fondu01 = fondu01 + 1;
    analogWrite(PIN_LED_STRIP_01, fondu01);
  } else {
    fondu01 = 0;
  }
//fondu lumineux de la led strip #1 branchée sur le pin 9 de l'arduino
  if (fondu02 > 0) {
    fondu02 = fondu02 - 1;
    analogWrite(PIN_LED_STRIP_02, fondu02);
  } else {
    fondu02 = 255;
  }
  
  delay(vitesseFondus);
}
