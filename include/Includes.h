
#pragma once
//_____________________typical arduino
#include "Arduino.h"
#include "FS.h"
#include "SPI.h"
#include <TFT_eSPI.h>

#include <MFRC522.h> //rfid controller
#include <Preferences.h> // for memory system

#include <PulseSensorPlayground.h>

#include <Beeper.h>

//_____________________________mine

#include "pin_control.h"
#include "Variables.h"
#include "Define_stuff.h"
#include "Orbitron_Bold_26.h" //just my font

//_____// sprites for buttons
#include "OF.h"
#include "ON.h"

//____________________________typical c++
#include <map>
#include <array>
#include <string>