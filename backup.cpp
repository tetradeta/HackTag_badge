
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


//________________________MENU.FUNCTIONS________________________\\

// =============================
// Background Grid
// =============================
void drawGrid()
{
  for (int x = 0; x < SCR_W; x += GRID_SPACING)
    tft.drawFastVLine(x, 0, SCR_H, DIM);

  for (int y = 0; y < SCR_H; y += GRID_SPACING)
    tft.drawFastHLine(0, y, SCR_W, DIM);
}

// =============================
// Scanlines Effect
// =============================
void drawScanlines()
{
  for (int y = 0; y < SCR_H; y += SCANLINE_STEP)
    tft.drawFastHLine(0, y, SCR_W, SCANLINE_CLR);
}

// =============================
// HUD Outer Frame
// =============================
void drawOuterFrame()
{
  // Top left
  tft.drawLine(0, 0, FRAME_INSET, 0, NEON);
  tft.drawLine(0, 0, 0, FRAME_INSET, NEON);
  tft.drawLine(FRAME_INSET, 0, FRAME_INSET + CORNER_OFFSET, CORNER_OFFSET, NEON);
  tft.drawLine(0, FRAME_INSET, CORNER_OFFSET, FRAME_INSET + CORNER_OFFSET, NEON);

  // Top right
  tft.drawLine(SCR_MAX_X, 0, SCR_MAX_X - FRAME_INSET, 0, NEON);
  tft.drawLine(SCR_MAX_X, 0, SCR_MAX_X, FRAME_INSET, NEON);
  tft.drawLine(SCR_MAX_X - FRAME_INSET, 0,
               SCR_MAX_X - FRAME_INSET - CORNER_OFFSET, CORNER_OFFSET, NEON);
  tft.drawLine(SCR_MAX_X, FRAME_INSET,
               SCR_MAX_X - CORNER_OFFSET, FRAME_INSET + CORNER_OFFSET, NEON);

  // Bottom left
  tft.drawLine(0, SCR_MAX_Y, FRAME_INSET, SCR_MAX_Y, NEON);
  tft.drawLine(0, SCR_MAX_Y, 0, SCR_MAX_Y - FRAME_INSET, NEON);
  tft.drawLine(FRAME_INSET, SCR_MAX_Y,
               FRAME_INSET + CORNER_OFFSET, SCR_MAX_Y - CORNER_OFFSET, NEON);
  tft.drawLine(0, SCR_MAX_Y - FRAME_INSET,
               CORNER_OFFSET, SCR_MAX_Y - FRAME_INSET - CORNER_OFFSET, NEON);

  // Bottom right
  tft.drawLine(SCR_MAX_X, SCR_MAX_Y, SCR_MAX_X - FRAME_INSET, SCR_MAX_Y, NEON);
  tft.drawLine(SCR_MAX_X, SCR_MAX_Y, SCR_MAX_X, SCR_MAX_Y - FRAME_INSET, NEON);
  tft.drawLine(SCR_MAX_X - FRAME_INSET, SCR_MAX_Y,
               SCR_MAX_X - FRAME_INSET - CORNER_OFFSET, SCR_MAX_Y - CORNER_OFFSET, NEON);
  tft.drawLine(SCR_MAX_X, SCR_MAX_Y - FRAME_INSET,
               SCR_MAX_X - CORNER_OFFSET, SCR_MAX_Y - FRAME_INSET - CORNER_OFFSET, NEON);
}

// =============================
// Side Tech Bars
// =============================
void drawSidePanels()
{
  // Left vertical segmented bar
  for (int y = BAR_START_Y; y < BAR_END_Y; y += BAR_STEP)
  {
    tft.fillRect(BAR_LEFT_X, y, BAR_WIDTH, BAR_HEIGHT, DARK);
    tft.drawRect(BAR_LEFT_X, y, BAR_WIDTH, BAR_HEIGHT, NEON);
  }

  // Right vertical segmented bar
  for (int y = BAR_START_Y; y < BAR_END_Y; y += BAR_STEP)
  {
    tft.fillRect(BAR_RIGHT_X, y, BAR_WIDTH, BAR_HEIGHT, DARK);
    tft.drawRect(BAR_RIGHT_X, y, BAR_WIDTH, BAR_HEIGHT, NEON);
  }
}

// =============================
// Center Decorative Core
// =============================
void drawCenterCore()
{
  int cx = CENTER_X;
  int cy = CENTER_Y;

  tft.drawCircle(cx, cy, CORE_RAD_LG, NEON);
  tft.drawCircle(cx, cy, CORE_RAD_MD, DARK);
  tft.drawCircle(cx, cy, CORE_RAD_SM, NEON);

  tft.drawLine(cx - CORE_LINE_LEN, cy, cx + CORE_LINE_LEN, cy, DARK);
  tft.drawLine(cx, cy - CORE_LINE_LEN, cx, cy + CORE_LINE_LEN, DARK);
}


// when selected button changed u gotta redraw it
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

void back_from_feature()
{
    functioning = false;
    funct_flag = false;
    draw_all_new_buttons();
    m = 8;
    draw_set_of_buttons(m - menu_coefficient - Pressed);
    Serial.println("hey");
}


//________________________SETUP________________________\\


void setup() {
  Serial.begin(115200);
  SPI.begin();
  preferences.begin("Memory", false); // non volatile memory
//_______________________________________________________RFID

  mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// just for fun (for board to init properly)
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
  set_UIDs();

  Serial.println(preferences.getChar("score", 0));
//________________________________________DISPLAY_AND_SPRITES


  tft.init();
  tft.setRotation(0);
  tft.setSwapBytes(true); 
  tft.fillScreen(TFT_BLACK);
  tft.loadFont(Orbitron_Bold_26);

  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextDatum(TL_DATUM);

  tft.setSwapBytes(true);

  but_on.createSprite(200, 50);
  but_off.createSprite(200, 50);

  but_on.setSwapBytes(true);
  but_off.setSwapBytes(true);

  but_on.pushImage(0,0,200,50,ON);
  but_off.pushImage(0,0,200,50,OF);



//________________________________________PinsCONTROL

//buttons
pinMode(Select_Button_Purple, INPUT_PULLUP);
pinMode(Up_Button_Green, INPUT_PULLUP);
pinMode(Down_Button_Blue, INPUT_PULLUP);

//laser
pinMode(Laser_pin,OUTPUT);
digitalWrite(Laser_pin, LOW);
}

void loop()
{

  if(up_btn.click() && !functioning){
  m=m+Pressed;
  Serial.println(m);
  }

  if(down_btn.click() && !functioning){
  m=m-Pressed;
  Serial.println(m);
  }

  if(m==-1){m=5;} // when press up at the upper button it jumps on "GUIDE"

  buz.tick(); //dont mind me. Here just for beeper library

  switch (m)
  {
//_________________________________________________________MAIN.MENU_________________________________________________

    //..............................BACK..............................
  case 0:
    draw_all_new_buttons();
    draw_set_of_buttons(m);
    if (selected_btn.click())
    {
      Serial.println("BACK");
      draw_all_new_buttons();
    }
    break;

    //..............................ANNOUNCE..........................
  case 1:
    draw_set_of_buttons(m);
    if (selected_btn.click())
    {
      Serial.println("ANNOUNCE");
    }
    break;

    //..............................RATING..........................
  case 2:
    draw_set_of_buttons(m);
    if (selected_btn.click())
    {
      Serial.println("RATING");
    }
    break;

    //..............................TOOLS..........................
  case 3:
    draw_set_of_buttons(m);
    if (selected_btn.click())
    {
      Serial.println("TOOLS");
      m = m+5;
      Serial.println(m);
    }
    break;

    //..............................SETTINGS..........................
  case 4:
    draw_set_of_buttons(m);
    if (selected_btn.click())
    {
      Serial.println("SETTINGS");
    }
    break;

    //..............................GUIDE..........................
  case 5:
    draw_set_of_buttons(m);
    if (selected_btn.click())
    {
      Serial.println("GUIDE");
    }
    break;

    //___________return to the first
  case 6:
    m = 0;
    break;
  
//_______________________________________________________________________________________________ANNOUNCE.MENU_______________________________//
//_______________________________________________________________________________________________RATING.MENU_________________________________//
//_______________________________________________________________________________________________TOOLS.MENU__________________________________//
  case 7:
    m = 13;
    break;
//************BACK
  case 8:
   menu_coefficient = 7;
   draw_all_new_buttons();
   draw_set_of_buttons(m-menu_coefficient-Pressed); //I know thats idiotic but 

  if (selected_btn.click())
  {
    Serial.println("BACK TO MAIN");
    menu_coefficient = 0;
    m = 0;
  }
   break;
//************FLASHLIGHT
  case 9:
    draw_set_of_buttons(m-menu_coefficient-Pressed);
    break;
//************NFC
  case 10:
  draw_set_of_buttons(m-menu_coefficient-Pressed);
	if (selected_btn.click()){functioning=true;funct_flag=0;}
	while(functioning)
	{
    if(!funct_flag)
    {
      tft.fillScreen(BG);
      drawGrid();
      drawScanlines();
      drawOuterFrame();
      drawCenterCore();
		  tft.drawString("Waiting for rfid...", TEXT_center_X, TEXT_center_Y);
      funct_flag = true;
    }
    if (selected_btn.click())
    {
    tft.fillScreen(BG);
    functioning = false;
    funct_flag = false;
    draw_all_new_buttons();
    m = 8;
    draw_set_of_buttons(m - menu_coefficient - Pressed);
    }

		// Do nothing if there is no card
		if (!mfrc522.PICC_IsNewCardPresent()){continue;}
		// Select one of the cards
		if (!mfrc522.PICC_ReadCardSerial()){continue;}
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

		// convert array to std readable

		for (byte i = 0; i < 4; i++)
		{
			Trans_array[i] = mfrc522.uid.uidByte[i];
		}
		//_______________________________

		auto it = myMap.find(Trans_array); 

		if (it!=myMap.end() && preferences.getBool(it->second.c_str(), true) && millis()-last_time>TimeOut)
		{
			last_time = millis();
			Serial.println("works");
      preferences.putBool(it->second.c_str(), false);
      preferences.putChar("score", preferences.getChar("score", 0) + 1);
      Serial.println(preferences.getChar("score", 0));
		}else if (millis() - last_time > TimeOut)
    {
      Serial.println("nice try");
      last_time = millis();
    }
	}
	break;
//************WEATHER
  case 11:
    draw_set_of_buttons(m-menu_coefficient-Pressed);
    break;
//************LASER
  case 12:
    draw_set_of_buttons(m-menu_coefficient-Pressed);
    if (selected_btn.click() && !functioning){functioning=true;funct_flag=0;}
    while (functioning)
    {
      if (!funct_flag)
      {
        tft.fillScreen(TFT_BLACK);
        tft.drawString("UP", TEXT_center_X, TEXT_center_Y);
        funct_flag = true;
      }

      digitalWrite(Laser_pin, !digitalRead(Up_Button_Green));

      if (selected_btn.click())
      {
        tft.fillScreen(BG);
        functioning = false;
        funct_flag = false;
        draw_all_new_buttons();
        m = 8;
        draw_set_of_buttons(m - menu_coefficient - Pressed);
      }
    }
    break;
//************HEARTRATE
  case 13:
    draw_set_of_buttons(m-menu_coefficient-Pressed);
    break;

  case 14:
    m = 8;
    break;

//_______________________________________________________________________________________________SETTINGS.MENU_______________________________//
//_______________________________________________________________________________________________GUIDE.MENU__________________________________//
  }
}