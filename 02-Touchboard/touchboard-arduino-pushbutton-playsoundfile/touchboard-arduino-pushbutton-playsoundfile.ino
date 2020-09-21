// -------------------- Touchboard

// compiler error handling
#include "Compiler_Errors.h"

// touch includes
#include <MPR121.h>
#include <Wire.h>
#define MPR121_ADDR 0x5C
#define MPR121_INT 4

// mp3 includes
#include <SPI.h>
#include <SdFat.h>
#include <FreeStack.h>
#include <SFEMP3Shield.h>

// mp3 variables
SFEMP3Shield MP3player;
byte result;
//int lastPlayed = 0;

// mp3 behaviour defines
#define REPLAY_MODE TRUE  // By default, touching an electrode repeatedly will 
// play the track again from the start each time.
//
// If you set this to FALSE, repeatedly touching an
// electrode will stop the track if it is already
// playing, or play it from the start if it is not.

// sd card instantiation
SdFat sd;

// ------------------ Button
const int buttonPin = 4;
int buttonState = 0; // initialisation de la valeur du bouton

void setup() {
  Serial.begin(57600);

  pinMode(LED_BUILTIN, OUTPUT);

  while (!Serial) ; {} //uncomment when using the serial monitor
  Serial.println("Bare Conductive Touch MP3 player");

  // initialisatisation du pin 2 (input) pour recevoir les information du bouton
  pinMode(buttonPin, INPUT);

  // ------ Initialisation Carte SD
  if (!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();
  // ------ Initialisation Touchboard Impedance


  // ------ Initialisation Lecteur MP3
  result = MP3player.begin();
  //Réglage du volume stéréo (Right/10, Left/10)
  MP3player.setVolume(10, 10);

  // Debug -- Affichage console des erreurs
  if (result != 0) {
    Serial.println("Error code: ");
    Serial.println(result);
    Serial.println(" when trying to start MP3 player");
  }
}

void loop() {
  // Lecture de la valeur du bouton
  buttonState = digitalRead(buttonPin);
  // Si le bouton est pressé…
  if (buttonState == HIGH) {
    Serial.println("bouton pressé ");
    // … si le mp3 est en lecture
    if (MP3player.isPlaying()) {
      if ( !REPLAY_MODE ) {
        // if we're already playing the requested track, stop it
        // (but only if we're not in REPLAY_MODE)
        MP3player.stopTrack();
        Serial.println("stopping track ");
      } else { // … si le mp3 n'est pas en lecture
        MP3player.stopTrack();
        MP3player.playTrack(0);
        Serial.println("playing track TRACK000.mp3");
      }
    }
  }else{
     MP3player.stopTrack();
    Serial.println("bouton pas pressé ");
  }
}
