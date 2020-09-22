// which digital pin we're going to use
#define PIN 9// how fast you want it to cycle, higher is slower
#define FADESPEED 7

void setup() {
  Serial.begin(9600);
  pinMode(PIN, OUTPUT);
}


void loop() {
  int i;

  // fade from low to high (note we can't go to 256)
  for (i = 0; i < 255; i++) {
    analogWrite(PIN, i);
    delay(FADESPEED);
  }// then high to low
  for (i = 255; i > 0; i--) {
    analogWrite(PIN, i);
    delay(FADESPEED);
  }// pause in between
  delay(50);

}
