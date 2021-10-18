#include <SPI.h>
#include <RFID.h> // à télécharger pour installation ici : https://github.com/miguelbalboa/rfid

// Déclaration des modules
RFID monModuleRFID01(2, 9); // SDA, RST
RFID monModuleRFID02(3, 9); // SDA, RST
RFID monModuleRFID03(4, 9); // SDA, RST

int UID[5];

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  monModuleRFID.init();

}

void loop()
{
  //======== Module 1
  if (monModuleRFID01.isCard()) {
    if (monModuleRFID01.readCardSerial()) {
      Serial.print("L'UID est: ");
      for (int i = 0; i <= 4; i++)
      {
        UID[i] = monModuleRFID01.serNum[i];
        Serial.print(UID[i], DEC);
        Serial.print(".");
      }
      Serial.println("");
    }
    monModuleRFID01.halt();
  }
  //======== Module 2
  delay(1);
  if (monModuleRFID02.isCard()) {
    if (monModuleRFID02.readCardSerial()) {
      Serial.print("L'UID est: ");
      for (int i = 0; i <= 4; i++)
      {
        UID[i] = monModuleRFID02.serNum[i];
        Serial.print(UID[i], DEC);
        Serial.print(".");
      }
      Serial.println("");
    }
    monModuleRFID02.halt();
  }
  delay(1);
  //======== Module 3
  delay(1);
  if (monModuleRFID03.isCard()) {
    if (monModuleRFID03.readCardSerial()) {
      Serial.print("L'UID est: ");
      for (int i = 0; i <= 4; i++)
      {
        UID[i] = monModuleRFID03.serNum[i];
        Serial.print(UID[i], DEC);
        Serial.print(".");
      }
      Serial.println("");
    }
    monModuleRFID03.halt();
  }
  delay(1);
}
