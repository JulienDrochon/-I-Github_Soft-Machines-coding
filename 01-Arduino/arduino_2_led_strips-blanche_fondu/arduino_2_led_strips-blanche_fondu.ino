// which digital pin we're going to use
#define PIN_LED_STRIP_01 9// pin arduino où est raccordé la première led strip = pin 9
#define PIN_LED_STRIP_02 6// pin arduino où est raccordé la deuxième led strip = pin 6
#define FADESPEED 7

// déclaration variables
int fondu01 = 0;
int fondu02 = 255;

void setup() {
  pinMode(PIN_LED_STRIP_01, OUTPUT);
  pinMode(PIN_LED_STRIP_02, OUTPUT);
}


void loop() {
  if (fondu01 < 255) {
    fondu01 = fondu01 + 1;
    analogWrite(PIN_LED_STRIP_01, fondu01);
  } else {
    fondu01 = 0;
  }

  if (fondu02 > 0) {
    fondu02 = fondu02 - 1;
    analogWrite(PIN_LED_STRIP_02, fondu02);
  } else {
    fondue02 = 255;
  }
}
