#pragma once


// menu define's
#define But_space 52
#define But_X 21
#define But_Y 7
#define TEXT_center_X 120
#define TEXT_center_Y 33

// common value define's

#define Pressed 1

#define TimeOut 1500 // 1.5 seconds




// Tried to do something not so bad... But that just never a case...

#define NEON         0x07E0
#define DARK         0x0320
#define DIM          0x0100
#define BG           TFT_BLACK
#define SCANLINE_CLR 0x0120

// Display dimensions
#define SCR_W        240
#define SCR_H        320
#define SCR_MAX_X    (SCR_W - 1)   // 239
#define SCR_MAX_Y    (SCR_H - 1)   // 319

// Grid
#define GRID_SPACING 20

// Outer frame
#define FRAME_INSET   50
#define CORNER_OFFSET 20

// Side bars
#define BAR_LEFT_X    8
#define BAR_WIDTH     6
#define BAR_HEIGHT    18
#define BAR_START_Y   40
#define BAR_END_Y     280
#define BAR_STEP      30
#define BAR_RIGHT_X   (SCR_W - BAR_LEFT_X - BAR_WIDTH)  // 226

// Center core
#define CENTER_X      (SCR_W / 2)   // 120
#define CENTER_Y      (SCR_H / 2)   // 160
#define CORE_RAD_LG   60
#define CORE_RAD_MD   40
#define CORE_RAD_SM   20
#define CORE_LINE_LEN 80

// Scanlines
#define SCANLINE_STEP 4