// Déclaration de variables
int sensorValue0; // pour les données de la premiere photocell
int sensorValue1; // pour les données de la deuxieme photocell
int pin0 = A0; // pour déterminer quelle entrée est utilisé par la première photocell sur la carte Arduino
int pin1 = A1; // pour déterminer quelle entrée est utilisé par la deuxième photocell sur la carte Arduino

// Initialisation de la carte
void setup() {
  // initialisation du port série à un débit de 9600 par seconde
  Serial.begin(9600);
}

void loop() {
  // On attribue à la variable sensorValue0 les données analogiques reçu sur la broche
  // A0 de l'ordinateur. La fonction analogRead() permet de faire cela.
  sensorValue0 = analogRead(pin0);
  // On attribue à la variable sensorValue1 les données analogiques reçu sur la broche
  // A1 de l'ordinateur. La fonction analogRead() permet de faire cela.
  sensorValue1 = analogRead(pin1);
  // On envoie les valeurs des variables sensorValue0 et sensorValue1
  // au port série de l'ordinateur
  Serial.print(sensorValue0);
  Serial.print("\t");
  Serial.println(sensorValue1);
  delay(50);        // Delai de 1 milliseconde pour stabiliser le transfert

}
