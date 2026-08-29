
#include "Includes.h"

#include "Functions.h"


//________________________INITIALIZATION__________________\\
//tft
TFT_eSprite but_on = TFT_eSprite(&tft);
TFT_eSprite but_off = TFT_eSprite(&tft);
//buttons
Button up_btn(Up_Button_Green);
Button down_btn(Down_Button_Blue);
Button selected_btn(Select_Button_Purple);
//rfid
MFRC522 mfrc522(RfId_CS, RfId_RST);
//non volatile memory
Preferences preferences;

void draw_set_of_buttons(int m)
{
  if ((m+menu_coefficient) != menu_flag)
  {

    int v1 = m - 1;
    int v2 = m + 1;
    but_on.pushSprite(But_X, But_Y + (m)*But_space);

    tft.setTextColor(TFT_BLACK, TFT_GREEN);
    tft.drawString(names[m+menu_coefficient], TEXT_center_X, TEXT_center_Y + (m)*But_space);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);

    if (v2 == 6)
    {
      but_off.pushSprite(But_X, But_Y + (0) * But_space);
      tft.drawString(names[0+menu_coefficient], TEXT_center_X, TEXT_center_Y + (0) * But_space);
    }
    else
    {
      but_off.pushSprite(But_X, But_Y + (v2)*But_space);
      tft.drawString(names[v2+menu_coefficient], TEXT_center_X, TEXT_center_Y + (v2)*But_space);
    }
    
    if (v1 == -1)
    {
      but_off.pushSprite(But_X, But_Y + (m + 5) * But_space);
      tft.drawString(names[5+menu_coefficient], TEXT_center_X, TEXT_center_Y + (5) * But_space);
    }
    else
    {
      but_off.pushSprite(But_X, But_Y + v1 * But_space);
      tft.drawString(names[v1+menu_coefficient], TEXT_center_X, TEXT_center_Y + (v1)*But_space);
    }
    menu_flag = (m+menu_coefficient);
  }
}
// when menu changed u gotta redraw ALL OF IT
void draw_all_new_buttons()
{
  if (m != draw_menu_flag)
  {
    for (byte n = m, counter = 0; counter < 7; counter++, n++)
    {
      but_off.pushSprite(21, 7 + (n - menu_coefficient) * 52);
      tft.setTextDatum(MC_DATUM);
      tft.drawString(names[n], 120, 33 + (n - menu_coefficient) * 52);
      Serial.println(n);
    }
    draw_menu_flag = m;
  }
}

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