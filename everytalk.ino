#include "SPI.h"
#include <TinyGPS.h>
#include <ILI9488.h>
#include <TFT_Touch.h>
#include <Adafruit_GFX.h>
#include <HardwareSerial.h>
#include <MapleFreeRTOS821.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>

// ILI9488 pin allocation
#define TFT_DC    PA2
#define TFT_CS    PA0
#define TFT_RST   PA1
#define TFT_CLK   PA5
#define TFT_MISO  PA6
#define TFT_MOSI  PA7
#define TFT_BL    PB8

// XPT2046 pin allocation
#define DOUT      PB12
#define DIN       PB13
#define DCS       PA9
#define DCLK      PA8

// Range of TS coordinate value (Raw) : 0 ~ 4095
#define HMIN      220 // Horizontal
#define HMAX      3875
#define VMIN      250 // Vertical
#define VMAX      3947
#define XYSWAP    0

// LCD resolution definition
#define HRES      320
#define VRES      480

int xPerTouch = ( HMAX - HMIN ) / HRES; // X
int yPerTouch = ( VMAX - VMIN ) / VRES; // Y
uint8_t currentMenu = 0; // Main menu
bool isCalibrated = 0;

TinyGPS gps;
ILI9488 tft = ILI9488(TFT_CS, TFT_DC, TFT_RST);
TFT_Touch touch = TFT_Touch(DCS, DCLK, DIN, DOUT);

void setup() {
  Serial3.begin(9600); // Allocate UART3 for GPS.
  Serial2.begin(19200); // Allocate UART2 for Iridium transceiver.
  tft.begin();
  tft.setRotation(4);
  touch.setCal(HMIN, HMAX, VMIN, VMAX, HRES, VRES, XYSWAP); // Raw xmin, xmax, ymin, ymax, width, height
  touch.setRotation(1);
  pinMode(TFT_BL, OUTPUT);
  tft.fillScreen(ILI9488_BLACK);
  tft.setFont(&FreeSans18pt7b);
  tft.setTextColor(ILI9488_WHITE); tft.setTextSize(1);
  tft.setCursor(85, 180); tft.print("EveryTalk");
  tft.setFont(); tft.setCursor(122, 460); tft.print("made by L0G1C");
  tft.setFont(&FreeSans12pt7b);
  digitalWrite(TFT_BL, HIGH);
}

void loop(void) {
  caliScr();
}

unsigned long caliScr() {
  unsigned int X1_Raw;
  unsigned int Y1_Raw;

    tft.drawFastHLine(10, VRES - 20, 20, ILI9488_RED); // x=20, y=460
    tft.drawFastVLine(20, VRES - 30, 20, ILI9488_RED);

    tft.drawFastHLine(HRES - 30, 20, 20, ILI9488_RED); // x=300, y=20
    tft.drawFastVLine(HRES - 20, 10, 20, ILI9488_RED);

  while (touch.Pressed()) // Note this function updates coordinates stored within library variables
  {
    X1_Raw = touch.RawX();
    Y1_Raw = touch.RawY(); // #1 Raw TS value, (20, 20)

    tft.setCursor(1, 20);
    tft.fillScreen(0xFFFF);
    tft.setTextColor(ILI9488_BLACK);
    tft.print(X1_Raw);
    tft.print(", ");
    tft.print(Y1_Raw);

    delay(10);
  }
}
