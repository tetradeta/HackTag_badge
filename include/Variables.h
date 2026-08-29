#pragma once

#include <map>
#include <array>

//___________________________________________MENU RELATED___________________________________________________

int m = 0; // menu variable used in switch

int menu_flag = 1; // for no repeats of switch function

int draw_menu_flag = 1;

byte menu_coefficient = 0;


bool functioning = 0;

bool funct_flag = 0; // for one-use tasks inside if statements

char names[14][13] = {    //  ___________menu's____________
    "BACK",         // 0
    "ANNOUNCE",     // 1
    "RATING",       // 2
    "TOOLS",        // 3
    "SETTINGS",     // 4
    "GUIDE",        // 5
    " ",            // Tools menu hits:
    "BACK",         // 7
    "FLASHLIGHT",   // 8
    "NFC",          // 9
    "WEATHER",      // 10
    "LASER",        // 11
    "HEARTRATE",    // 12
    " ",            // Settings menu hits
};

//___________________________________________RFID RELATED___________________________________________________

std::map<std::array<byte, 4>, std::string> myMap; // container for rfid
std::array<byte, 4> Trans_array; // translation to std::array of arrays used in rfid library


//___correct uid's

void set_UIDs()
{
    myMap[{0x07, 0x1E, 0x67, 0x33}] = "Rfid_1";
    myMap[{0x72, 0x33, 0x1A, 0x20}] = "Rfid_2";
}


