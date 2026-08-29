#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

// Color palette
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

// =============================

void setup()
{
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(BG);

  drawGrid();
  drawScanlines();
  drawOuterFrame();
  drawSidePanels();
}

void loop()
{
}