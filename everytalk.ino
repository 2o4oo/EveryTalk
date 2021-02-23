// Project EveryTalk - Main
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
#define DCLK      PA8
#define DCS       PA9
#define DOUT      PB12
#define DIN       PB13

// IRQ pin allocations
#define IRQ_SLEP  PA4
#define IRQ_TS    PB0

// LCD resolution
#define HRES      320
#define VRES      480

// Touch constants
#define TS_XM     0.08510
#define TS_XC     14.31656
#define TS_YM     -0.13142
#define TS_YC     518.87694

typedef struct {
  byte X_Scr;
  byte Y_Scr;
} TSLocation;

TinyGPS gps;
ILI9488 tft = ILI9488(TFT_CS, TFT_DC, TFT_RST);
TFT_Touch touch = TFT_Touch(DCS, DCLK, DIN, DOUT);
// Create task handle
TaskHandle_t ui_MainHandle;
TaskHandle_t tsMgrHandle;
// Create queue handle
QueueHandle_t touchData;
// Create semaphore handle TX on UART3
SemaphoreHandle_t uartSem;

void setup() {
  Serial3.begin(9600); // Allocate UART3 for GPS.
  Serial2.begin(19200); // Allocate UART2 for Iridium transceiver.
  attachInterrupt(IRQ_TS, interruptHandler, RISING);
  tft.begin();
  pinMode(TFT_BL, OUTPUT);
  tft.setRotation(4);
  touch.setRotation(1);
  // Draw splash screen
  tft.fillScreen(ILI9488_WHITE);
  tft.setFont(&FreeSans18pt7b);
  tft.setTextColor(ILI9488_BLACK); tft.setTextSize(1);
  tft.setCursor(85, 180); tft.print("EveryTalk");
  tft.setFont();
  tft.setCursor(122, 460); tft.print("made by L0G1C");
  tft.setFont(&FreeSans12pt7b);
  tft.setCursor(5, 20);
  // Turn on backlight
  digitalWrite(TFT_BL, HIGH);
  Serial3.println("[Startup] Startup process done.");
  // Belows are for FreeRTOS
  // Tasks creation
  xTaskCreate(tsMgr, "tsMgr", configMINIMAL_STACK_SIZE, NULL, 2, &tsMgrHandle);
  xTaskCreate(ui_Main, "ui_Main", configMINIMAL_STACK_SIZE, NULL, 2, &ui_MainHandle);
  // Create queue for can makes TSManager send touch data to ui_Main.
  touchData = xQueueCreate(1, sizeof(TSLocation));
  vTaskStartScheduler();
  }
