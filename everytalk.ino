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

TinyGPS gps;
ILI9488 tft = ILI9488(TFT_CS, TFT_DC, TFT_RST);
TFT_Touch touch = TFT_Touch(DCS, DCLK, DIN, DOUT);

void setup() {
  Serial3.begin(9600); // Allocate UART3 for GPS.
  Serial2.begin(19200); // Allocate UART2 for Iridium transceiver.
  Serial.begin(9600);
  tft.begin();
  tft.setRotation(4);
  //touch.setCal(HMIN, HMAX, VMIN, VMAX, HRES, VRES, XYSWAP); // Raw xmin, xmax, ymin, ymax, width, height
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
  touchTest();
}

unsigned long touchTest() {
  float X_Raw;
  float Y_Raw;
  float Xm = 0.085106;
  float Xc = 8.31656;
  float Ym = -0.13142;
  float Yc = 518.87694;
  uint16_t Xpx;
  uint16_t Ypx;

  while (touch.Pressed()) // Note this function updates coordinates stored within library variables
  {
    X_Raw = touch.RawX();
    Y_Raw = touch.RawY();

    Xpx = ((Xm * X_Raw) - Xc);
    Ypx = ((Ym * Y_Raw) + Yc);
    
    tft.drawPixel(Xpx, Ypx, ILI9488_RED);
  }
}
