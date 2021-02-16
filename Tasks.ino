// EveryTalk Project - Tasks
static void gpsManager(void *pvParameters) {
  for(;;) {
    
  }
}
static void backlightManager(void *pvParameters) {
  for(;;) {
    
  }
}
static void touchManager(void *pvParameters) {
  for(;;) {
  uint16_t X_px;
  uint16_t Y_px;

  while (touch.Pressed()) // Updates coordinates stored within library variables
  {
    X_px = ((touch.RawX() * TS_XM) - TS_XC);
    Y_px = ((touch.RawY() * TS_YM) + TS_YC);

    if (2048.0 < touch.RawY()) { // Y_px correction. If your touch panel is accurate enough, it's okay to remove this section. 
      Y_px = Y_px + ((239 - Y_px) * 0.01673);
      } else if (touch.RawY() < 2048.0) {
      Y_px = Y_px - (Y_px * 0.02092);
      }
   }
   // Return screen coordinates...
  }
}
