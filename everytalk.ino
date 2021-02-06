#include "SPI.h"
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

ILI9488 tft = ILI9488(TFT_CS, TFT_DC, TFT_RST);
TFT_Touch touch = TFT_Touch(DCS, DCLK, DIN, DOUT);

void setup() {
  Serial3.begin(9600); // Allocate UART3 for GPS.
  Serial2.begin(19200); // Allocate UART2 for Iridium transceiver.
  tft.begin();
  tft.setRotation(4);
  touch.setCal(HMIN, HMAX, VMIN, VMAX, HRES, VRES, XYSWAP); // Raw xmin, xmax, ymin, ymax, width, height
  touch.setRotation(1);
  pinMode(Backlight, OUTPUT);
  tft.fillScreen(ILI9488_BLACK);
  tft.setFont(&FreeSans18pt7b);
  tft.setTextColor(ILI9488_WHITE);tft.setTextSize(1);
  tft.setCursor(85,180);tft.print("EveryTalk");
  tft.setFont();tft.setCursor(122,460);tft.print("made by L0G1C");
  tft.setFont(&FreeSans12pt7b);
  digitalWrite(Backlight, HIGH);
}

class ScreenPoint {
  public:
  int16_t scr_x;
  int16_t scr_y;
}

void loop(void) {
  caliScr();
}

void calibrateTS() {
  tft.drawFastHLine(10,20,20,ILI9488_RED);
  tft.drawFastVLine(20,10,20,ILI9488_RED);
  
}

unsigned long caliScr() {
  unsigned int X_Raw;
  unsigned int Y_Raw;

 if (touch.Pressed()) // Note this function updates coordinates stored within library variables
  { 
    X_Raw = touch.RawX();
    Y_Raw = touch.RawY();

    tft.setCursor(1,20);
    tft.fillScreen(0xFFFF);
    tft.setTextColor(ILI9488_BLACK);
    tft.print(X_Raw);
    tft.print(", ");
    tft.print(Y_Raw);
    
    tft.setCursor(1,50);
    tft.print(( X_Raw - HMIN ) / xPerTouch);
    tft.print(", ");
    tft.print(480 - ( ( Y_Raw - VMIN ) / yPerTouch));
    tft.drawPixel( ( X_Raw - HMIN ) / xPerTouch, 480 - ( ( Y_Raw - VMIN ) / yPerTouch) , ILI9488_RED );
    delay(10);
  }
}
