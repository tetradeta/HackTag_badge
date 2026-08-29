#include "Arduino.h"
#include <TJpg_Decoder.h>
#include "SD.h"
#include "FS.h"
#include "SPI.h"
#include <TFT_eSPI.h>

// ВАЖНО: Убедитесь, что пин 17 действительно подключен к CS SD-карты
#define SD_CS 17
#define RfId_CS 5

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

const char sprites[12][18] = {
    "/AnnounceOff.jpg",
    "/BackOff.jpg",
    "/GuideOff.jpg",
    "/RatingOff.jpg",
    "/SettingsOff.jpg",
    "/ToolsOff.jpg",
};


bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)

{
  if ( y >= tft.height() ) return 0;
  tft.pushImage(x, y, w, h, bitmap);
  return 1;
}


bool sprite_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
  // Рисуем не в tft, а в sprite!
  sprite.pushImage(x, y, w, h, bitmap);
  return 1;
}



void setup()
{
  Serial.begin(115200);
  // 1. Сначала глушим лишние устройства на шине SPI
  pinMode(RfId_CS, OUTPUT);
  digitalWrite(RfId_CS, HIGH); // Отключаем RFID
  
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);   // Отключаем SD пока что

  // 2. Инициализируем TFT ПЕРВЫМ!
  // Это важно, так как tft.begin() может изменить настройки SPI

  tft.begin();
  tft.setTextColor(0xFFFF, 0x0000);
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
  sprite.createSprite(202, 51);

  // 3. Теперь инициализируем SD карту

  SD.begin(SD_CS);

  TJpgDec.setCallback(sprite_output);

  TJpgDec.setJpgScale(1);
  TJpgDec.drawSdJpg(0, 0, "/Test2.jpg");
  sprite.setSwapBytes(true);
}

void loop()
{

  tft.fillScreen(TFT_RED); // Очистка экрана красным перед рисованием
  uint32_t t = millis();
  
  // Имя файла должно начинаться со слэша "/"
  // Убедитесь, что файл называется test.jpg на карте
  const char* fileName = "/Test.jpg";
  uint16_t w = 0, h = 0;


//*******************************************************_КАРТИНКА_********************************
  TJpgDec.setCallback(tft_output);
  TJpgDec.drawSdJpg(0, 0, fileName);
//*******************************************************_СПРАЙТ_********************************
for(byte n=0; n<7; n++){
    TJpgDec.setCallback(sprite_output);
    TJpgDec.drawSdJpg(0, 0, sprites[n]);
    sprite.pushSprite(2,17+n*30);
    Serial.print(n);
    Serial.print(sprites[n]);
}


Serial.print("1");

delay(100);

}