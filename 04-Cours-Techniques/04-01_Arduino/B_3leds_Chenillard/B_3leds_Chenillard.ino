// Initialisation des pins 8, 9, 10 comme sorties
void setup () {
  pinMode (8, OUTPUT) ;
  pinMode (9, OUTPUT) ;
  pinMode (10, OUTPUT) ;
}
 
// Fonction loop
void loop () {
  // Extinction de toutes les DEL au départ du programme
  for (byte i = 4 ; i <= 9 ; i++) {
    digitalWrite (i, LOW) ; // éteint la DEL reliée à la broche i
  }
 
  // Boucle pour faire flasher les DEL
  for (byte i = 4 ; i <= 9 ; i++) {
    digitalWrite (i, HIGH) ; // allume la DEL sur broche i
    delay (50) ; // durée du flash 50 millisecondes
    digitalWrite (i, LOW) ; // éteint la DEL
  }
 
  // délai de 500 millisecondes
  delay (500) ;
 
  // Recommence la séquence
}
