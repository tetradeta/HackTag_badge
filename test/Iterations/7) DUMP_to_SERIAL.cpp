
#include <TFT_eSPI.h>


TFT_eSPI tft=TFT_eSPI();


#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         27          // Configurable, see typical pin layout above
#define SS_PIN          5         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
	Serial.begin(115200);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));


  Serial.begin(115200);

  tft.init();

  tft.fillScreen(TFT_RED);

  pinMode(26, OUTPUT);
  analogWrite(26, LOW);
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

	// Dump debug info about the card; PICC_HaltA() is automatically called
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  Serial.print("UID: ");
  for (uint8_t i = 0; i < 10; i++) {           // Цикл на 4 итерации
    Serial.print("0x");                       // В формате HEX
    Serial.print(mfrc522.uid.uidByte[i], HEX);   // Выводим UID по байтам
    Serial.print(", ");
  }
  Serial.println("");
}