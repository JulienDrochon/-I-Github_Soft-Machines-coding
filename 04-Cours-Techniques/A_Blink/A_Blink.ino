//declaration des variables
const pinLed = 4;

// la fonction setup() est la fonction qui se lance une fois au début du programme
void setup() {
  // dire à la pin 4 digital qu'elle se comporte comme une sortie
  pinMode(pinLed, OUTPUT);
}

// la fonction loop() est une fonction qui tourne en boucle éternellement une fois que le setup s'est exécuté
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
