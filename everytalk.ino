// EveryTalk Project - Main
#include "SPI.h"
#include <TinyGPS.h>
#include <ILI9488.h>
#include <TFT_Touch.h>
#include <Adafruit_GFX.h>
#include <HardwareSerial.h>
#include <MapleFreeRTOS900.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>

// ILI9488 pin allocations
#define TFT_DC    PA2
#define TFT_CS    PA0
#define TFT_RST   PA1
#define TFT_CLK   PA5
#define TFT_MISO  PA6
#define TFT_MOSI  PA7
#define TFT_BL    PB8

// XPT2046 pin allocations
#define DOUT      PB12
#define DIN       PB13
#define DCS       PA9
#define DCLK      PA8

// LCD resolution
#define HRES      320
#define VRES      480

// Touch constants
#define TS_XM     0.08510
#define TS_XC     14.31656
#define TS_YM     -0.13142
#define TS_YC     518.87694

TinyGPS gps;
ILI9488 tft = ILI9488(TFT_CS, TFT_DC, TFT_RST);
TFT_Touch touch = TFT_Touch(DCS, DCLK, DIN, DOUT);

void setup() {
  Serial3.begin(9600); // Allocate UART3 for GPS.
  Serial2.begin(19200); // Allocate UART2 for Iridium transceiver.
  Serial.begin(9600);
  tft.begin();
  tft.setRotation(4);
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
