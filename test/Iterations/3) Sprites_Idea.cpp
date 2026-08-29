#include "Includes.h"
#include "Functions.h"

TFT_eSPI tft = TFT_eSPI();

TFT_eSprite sprite_Upper = TFT_eSprite(&tft);
TFT_eSprite sprite_Mid = TFT_eSprite(&tft);
TFT_eSprite sprite_Lower = TFT_eSprite(&tft);



void setup()
{

  Serial.begin(115200);
  // 1. Сначала глушим лишние устройства на шине SPI
  pinMode(RfId_CS, OUTPUT);
  digitalWrite(RfId_CS, HIGH); // Отключаем RFID

  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH); // Отключаем SD пока что

  // 2. Инициализируем TFT ПЕРВЫМ!
  // Это важно, так как tft.begin() может изменить настройки SPI

  tft.begin();
  tft.setTextColor(0xFFFF, 0x0000);
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);

  sprite_Upper.createSprite(202, 51);
  sprite_Mid.createSprite(202, 51);
  sprite_Lower.createSprite(202, 51);

  // 3. Теперь инициализируем SD карту

  SD.begin(SD_CS);

  TJpgDec.setCallback(Mid_sprite_output);

  TJpgDec.setJpgScale(1);
  TJpgDec.drawSdJpg(0, 0, "/Test2.jpg");

  sprite_Upper.setSwapBytes(true);
  sprite_Mid.setSwapBytes(true);
  sprite_Lower.setSwapBytes(true);

  TJpgDec.setCallback(tft_output);
  TJpgDec.drawSdJpg(0, 0, fileName);

  for (byte n = 0; n < 7; n++)
  {
    TJpgDec.setCallback(Mid_sprite_output);
    TJpgDec.drawSdJpg(0, 0, sprites[n]);
    sprite_Mid.pushSprite(21, 7 + n * 52);
  }
}

void loop()
{

  uint16_t w = 0, h = 0;

  for (m; m < 8; m++)
  {

    delay(500);
    switch (m)
    {

    case 1:

      m = 7;
      Serial.println("case 1");
      
    case 2:
    // Рисуем на дисплее
      sprite_Upper.pushSprite(21, 7 + (m-1) * 52);
      sprite_Mid.pushSprite(21, 7 + (m) * 52);
      sprite_Lower.pushSprite(21, 7 + (m+1) * 52);

    // Рисуем в спрайтах

      TJpgDec.setCallback(Upper_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[12]);

      TJpgDec.setCallback(Mid_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[1]);

      TJpgDec.setCallback(Lower_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[8]);

      Serial.println("case 2");

      break;


    case 3:
    // Рисуем на дисплее
      sprite_Upper.pushSprite(21, 7 + (m-1) * 52);
      sprite_Mid.pushSprite(21, 7 + (m) * 52);
      sprite_Lower.pushSprite(21, 7 + (m+1) * 52);

    // Рисуем в спрайтах

      TJpgDec.setCallback(Upper_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[12]);

      TJpgDec.setCallback(Mid_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[1]);

      TJpgDec.setCallback(Lower_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[8]);

      Serial.println("case 3");

      break;

    case 4:
    // Рисуем на дисплее
      sprite_Upper.pushSprite(21, 7 + (m-1) * 52);
      sprite_Mid.pushSprite(21, 7 + (m) * 52);
      sprite_Lower.pushSprite(21, 7 + (m+1) * 52);

    // Рисуем в спрайтах

      TJpgDec.setCallback(Upper_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[12]);

      TJpgDec.setCallback(Mid_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[1]);

      TJpgDec.setCallback(Lower_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[8]);

      Serial.println("case 4");

      break;

    case 5:
    // Рисуем на дисплее
      sprite_Upper.pushSprite(21, 7 + (m-1) * 52);
      sprite_Mid.pushSprite(21, 7 + (m) * 52);
      sprite_Lower.pushSprite(21, 7 + (m+1) * 52);

    // Рисуем в спрайтах

      TJpgDec.setCallback(Upper_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[12]);

      TJpgDec.setCallback(Mid_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[1]);

      TJpgDec.setCallback(Lower_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[8]);

      Serial.println("case 5");

      break;

    case 6:
    // Рисуем на дисплее
      sprite_Upper.pushSprite(21, 7 + (m-1) * 52);
      sprite_Mid.pushSprite(21, 7 + (m) * 52);
      sprite_Lower.pushSprite(21, 7 + (m+1) * 52);

    // Рисуем в спрайтах

      TJpgDec.setCallback(Upper_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[12]);

      TJpgDec.setCallback(Mid_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[1]);

      TJpgDec.setCallback(Lower_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[8]);

      Serial.println("case 6");

      break;

    case 7:
    // Рисуем на дисплее
      sprite_Upper.pushSprite(21, 7 + (m-1) * 52);
      sprite_Mid.pushSprite(21, 7 + (m) * 52);
      sprite_Lower.pushSprite(21, 7 + (m+1) * 52);

    // Рисуем в спрайтах

      TJpgDec.setCallback(Upper_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[12]);

      TJpgDec.setCallback(Mid_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[1]);

      TJpgDec.setCallback(Lower_sprite_output);
      TJpgDec.drawSdJpg(0, 0, sprites[8]);

      Serial.println("case 7");

      break;

    case 8:
      Serial.println("case 8");
      m = 2;
      break;
    }
  }


  //____________________MAIN MENU_______________//
}