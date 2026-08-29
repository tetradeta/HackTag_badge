#include <Preferences.h> 
#include <TFT_eSPI.h>
#include <SPI.h>
#include <MFRC522.h>
//_____________________
#include <map>
#include <array>
#include <string>

Preferences preferences;

TFT_eSPI tft=TFT_eSPI();


//______________________
std::map<std::array<byte, 4>, std::string> myMap;

std::array<byte, 4> Trans_array;

#define RST_PIN         27          // Configurable, see typical pin layout above
#define SS_PIN          5         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

long TMR = 0;

void setup() {
	Serial.begin(115200);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
    preferences.begin("Memory", false);


  tft.init();

  tft.fillScreen(TFT_RED);


	myMap[{0x07, 0x1E, 0x67, 0x33}] = "Rfid_1";

	myMap[{0x72, 0x33, 0x1A, 0x20}] = "Rfid_2";




}

void loop() {
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}


	for(byte i = 0; i<4;i++)
	{
		Trans_array[i] = mfrc522.uid.uidByte[i];
	}

  auto it = myMap.find(Trans_array); //?????????????????????????????????????????

  if(it!=myMap.end() && preferences.getBool(it->second.c_str(), true) && millis()-TMR>5000)
  {
	TMR = millis();
    Serial.println("works");
    preferences.putBool(it->second.c_str(), false);
  } else if(millis()-TMR>5000){Serial.println("nice try");TMR = millis();}

}