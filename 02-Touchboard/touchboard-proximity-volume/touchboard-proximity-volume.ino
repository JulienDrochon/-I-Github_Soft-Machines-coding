
/*******************************************************************************
  Controler le volume de la lecture d'un fichier son en fonction de la distance de la main avec une surface conductrice


  E0 est connecté à une électrode carrée de 85mmx85mm et E1, …, E11 jouent respectivementTRACK001.MP3 jusqu'à TRACK011.MP3. E0 contrôle le volume - une main plus proche diminue le volume, une main plus éloignée augmente le volume.

*******************************************************************************/

// Compileur pour afficher les erreurs
#include "Compiler_Errors.h"

// Inclusion des bibliothèques de la Touchboard
#include <MPR121.h>
#include <Wire.h>
#define MPR121_ADDR 0x5C
#define MPR121_INT 4

// Filtres et mapping pour les valeurs des capteurs
#define LOW_DIFF 0
#define HIGH_DIFF 50
#define filterWeight 0.3f // 0.0f to 1.0f - higher value = more smoothing
float lastProx = 0;

// Détermination de la borche pouvant reconnaitre la proximité, ici E0
#define PROX_ELECTRODE 0

// Bibliothèques pour la lectures des fichiers MP3
#include <SPI.h>
#include <SdFat.h>
#include <FreeStack.h>
#include <SFEMP3Shield.h>

// Variables pour les MP3
SFEMP3Shield MP3player;
byte result;
int lastPlayed = 0;
uint8_t volume = 0;

// Initialisation de la carte SD
SdFat sd;

// définition de la Led13 pour avoir un retour d'information lumineux
#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

void setup() {
  Serial.begin(57600);

  //Activation de la LED 13
  pinMode(LED_BUILTIN, OUTPUT);

  //while (!Serial) ; {} //décommenter pour utiliser le moniteur série

  //initialisation de la carte sd
  if (!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();

  //Initialisation du processeur pour la capacitance
  if (!MPR121.begin(MPR121_ADDR)) Serial.println("error setting up MPR121");
  MPR121.setInterruptPin(MPR121_INT);

  //Initialiation lecteur mp3
  result = MP3player.begin();
  MP3player.setVolume(volume, volume);

  //Afficher les erreurs
  if (result != 0) {
    Serial.print("Error code: ");
    Serial.print(result);
    Serial.println(" when trying to start MP3 player");
  }

  // ralentir une partie du filtrage de base du MPR121 pour éviter de
  // filtrer les mouvements lents des mains
  MPR121.setRegister(MPR121_NHDF, 0x01); //noise half delta (falling)
  MPR121.setRegister(MPR121_FDLF, 0x3F); //filter delay limit (falling)

}

void loop() {
  readTouchInputs();
}

// Fonction readTouchInputs()
void readTouchInputs() {
  //Updater tous les capteurs de capacitance
  MPR121.updateAll();

  // ne faire une action que si nous avons une ou plusieurs quilles touchées
  // ignorer les touches multiples

  for (int i = 1; i < 12; i++) { // Vérifier quelles électrodes ont été pressées
    if (MPR121.isNewTouch(i)) {

      //broche i viens d'être touché
      Serial.print("pin ");
      Serial.print(i);
      Serial.println(" was just touched");
      digitalWrite(LED_BUILTIN, HIGH);

      if (MP3player.isPlaying()) {
        if (lastPlayed == i) {
          // si nous jouons déjà le morceau demandé, arrêtez-le
          MP3player.stopTrack();
          Serial.print("stopping track ");
          Serial.println(i);
        } else {
          // si nous jouons déjà un morceau différent, arrêtez celui-là et jouez le nouveau morceau demandé
          MP3player.stopTrack();
          MP3player.playTrack(i);
          Serial.print("playing track ");
          Serial.println(i);

          // n'oubliez pas de mettre à jour lastPlayed - sans cela, 
          // nous n'avons pas d'histoirique de lecture
          lastPlayed = i;
        }
      } else {
        // si on ne joue rien, jouer le morceau demandé et
        // mettre à jour le dernier morceau joué
        MP3player.playTrack(i);
        Serial.print("playing track ");
        Serial.println(i);
        lastPlayed = i;
      }
    } else {
      if (MPR121.isNewRelease(i)) {
        Serial.print("pin ");
        Serial.print(i);
        Serial.println(" is no longer being touched");
        digitalWrite(LED_BUILTIN, LOW);
      }
    }
  }

  // lire la différence entre la ligne de base mesurée 
  // et les données continues mesurées
  int reading = MPR121.getBaselineData(PROX_ELECTRODE) - MPR121.getFilteredData(PROX_ELECTRODE);

  // imprimer la valeur de lecture pour le débogage
  Serial.print("Proximity electrode: ");
  Serial.println(reading);

  // limiter la lecture entre nos valeurs cartographiques basses et élevées
  unsigned int prox = constrain(reading, LOW_DIFF, HIGH_DIFF);

  // mettre en place un filtre de lissage simple (IIR lowpass)
  lastProx = (filterWeight * lastProx) + ((1 - filterWeight) * (float)prox);

  // map the LOW_DIFF..HIGH_DIFF range to 0 - > 254 (max range for MP3player.setVolume())
  uint8_t thisOutput = (uint8_t)map(lastProx, LOW_DIFF, HIGH_DIFF, 0, 254);

  // if((uint8_t)lastProx!=prox){ // only update volume if the value has changed
  // output the mapped value to the LED
  MP3player.setVolume(thisOutput, thisOutput);
  // }
}
