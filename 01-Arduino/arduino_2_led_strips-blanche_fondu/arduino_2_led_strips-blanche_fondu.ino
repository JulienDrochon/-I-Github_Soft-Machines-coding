//Déclaration de variables constantes
#define PIN_LED_STRIP_01 9// pin arduino où est raccordé la première led strip = pin 9
#define PIN_LED_STRIP_02 10// pin arduino où est raccordé la deuxième led strip = pin 10

// déclaration variables
int fondu01 = 0;
int fondu02 = 255;
int vitesseFondus = 5;
int fonduMontant01, fonduMontant02;

void setup() {
  Serial.begin(9600);
  //déclaration de la pin numérique 9 en tant que sortie
  pinMode(PIN_LED_STRIP_01, OUTPUT);
  //déclaration de la pin numérique 10 en tant que sortie
  pinMode(PIN_LED_STRIP_02, OUTPUT);
}


void loop() {
  // ------------------- Led Strip #1
  //fondu lumineux de la led strip #1 branchée sur le pin 9 de l'arduino
  if ( fondu01 == 255) {
    fonduMontant01 = -1;
  }
  if (fondu01 == 0) {
    fonduMontant01 = 1;
  }
  fondu01 = fondu01 + fonduMontant01;

  analogWrite(PIN_LED_STRIP_01, fondu01);

  // ------------------- Led Strip #2
  //fondu lumineux de la led strip #2 branchée sur le pin 10 de l'arduino
  if ( fondu02 == 255) {
    fonduMontant02 = -1;
  }
  if (fondu02 == 0) {
    fonduMontant02 = 1;
  }
  fondu02 = fondu02 + fonduMontant02;

  analogWrite(PIN_LED_STRIP_02, fondu02);

  delay(vitesseFondus);
}
