//declaration des variables
const pinLed = 4;

// la fonction setup() est la fonction qui se lance une fois au début du programme
void setup() {
  // dire à la pin 4 digital qu'elle se comporte comme une sortie
  pinMode(pinLed, OUTPUT);
}

// la fonction loop() est une fonction qui tourne en boucle éternellement une fois que le setup s'est exécuté
void loop() {
  digitalWrite(pinLed, HIGH);   // allumer la led. HIGH signifie qu'on lui donne du courant
  delay(1000);                       // attente d'une seconde
  digitalWrite(pinLed, LOW);    // éteindre la Led en coupant le courant
  delay(1000);                       // attente d'une seconde
}
