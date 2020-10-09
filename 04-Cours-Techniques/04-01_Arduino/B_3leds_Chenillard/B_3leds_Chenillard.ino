// Initialisation des lignes 4 à 9 en sortie
void setup () {
  pinMode (4, OUTPUT) ;
  pinMode (5, OUTPUT) ;
  pinMode (6, OUTPUT) ;
  pinMode (7, OUTPUT) ;
  pinMode (8, OUTPUT) ;
  pinMode (9, OUTPUT) ;
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
