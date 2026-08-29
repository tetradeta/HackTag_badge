
#include <SPI.h>
#include <MFRC522.h>
#include <Preferences.h>
#include <map>
#include <array>


Preferences preferences;

// контакты
#define SS_PIN 5
#define RST_PIN 27
#define BUTTON_PIN 22
#define Laser_Pin 32

MFRC522 mfrc522(SS_PIN, RST_PIN);

// Значения
#define BTN_DEB 50

// Разрешённый идентификатор Card UID
byte NFC_1[4] = {0x07, 0x1E, 0x67, 0x33};
byte NFC_2[4] = {0x72, 0x33, 0x1A, 0x20};


std::map<std::array<byte, 4>, bool> myMap;


boolean Used_1;
boolean Used_2;
byte User_Score;


unsigned long last_time;
unsigned long tmr;

void setup() {



  // пины
  pinMode(Laser_Pin, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(Laser_Pin, LOW);
  //база
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  //память
  preferences.begin("Memory", false);
  Used_1 = preferences.getUInt("Used_1", 0);
  Used_2 = preferences.getUInt("Used_2", 0);
  User_Score = preferences.getUInt("User_Score", 0);


//_______________________________


  myMap[{0x07, 0x1E, 0x67, 0x33}] = preferences.getUInt("RfId_1", 1);

  myMap[{0x72, 0x33, 0x1A, 0x20}] = preferences.getBool("RfId_2", 1);

  auto it = myMap.find({0x72, 0x33, 0x1A, 0x20}); //?????????????????????????????????????????

  if(it!=myMap.end() && it->second)
  {
    int score = 10;
    myMap[it->first] = true;
    preferences.putBool("RfId_2", false);
  }



}

void loop() {
    // Кнопка лазера
    if (millis() - tmr >= BTN_DEB && User_Score == 5 ) {
        tmr = millis();
        static bool pState = false;
        bool state = !digitalRead(BUTTON_PIN);
        if (pState != state) {  // состояние изменилось
            pState = state;     // запомнить новое
            if (state){
              digitalWrite(Laser_Pin, HIGH);
              Serial.println("Вы умрёте сейчас");
            }
            else{
              digitalWrite(Laser_Pin, LOW);
               Serial.println("Вы умрёте позже");
            } 
        }
    }

  // Ожидание
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;

  // чтение
  if ( !mfrc522.PICC_ReadCardSerial())
    return;

  for (byte i = 0; i < 4; i++) {
    // Если идентификатор не совпадает с заданным номером
    if (NFC_1[i] == mfrc522.uid.uidByte[i] && preferences.getUInt("Used_1", 0) == 0) {
      Used_1 = 1;
      User_Score = User_Score + 1;
      preferences.putUInt("Used_1", Used_1);
      preferences.putUInt("User_Score", User_Score);
      last_time = millis();
      Serial.println("10000 очков");
      //первый nfc
      return;
    }
    
    else if(NFC_2[i] == mfrc522.uid.uidByte[i] && preferences.getUInt("Used_2", 0) == 0) {
      Used_2 = 1;
      User_Score = User_Score + 4;
      preferences.putUInt("Used_2", Used_2);
      preferences.putUInt("User_Score", User_Score);
      last_time = millis();
      Serial.println("40000 очков");
      //второй nfc
    }

    else if(millis() - last_time > 1000){
      last_time = millis();
      Serial.println("Ага конечно");
      Serial.println(preferences.getUInt("User_Score", 0)*10000);
      Serial.println(preferences.getUInt("Used_1", 0));
      Serial.println(preferences.getUInt("Used_2", 0));
      //если метка неправильная или уже использовалась
    }

  }
}