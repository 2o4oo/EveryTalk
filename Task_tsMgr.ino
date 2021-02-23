// Project EveryTalk - tsMgr
static void tsMgr(void *params) {
  uint16_t X_px;
  uint16_t Y_px;
  
  TSLocation tsLoc;
  BaseType_t TsStat;

  for(;;) {
    // Updates coordinates stored within library variables
    while (touch.Pressed())
    { 
      X_px = ((touch.RawX() * TS_XM) - TS_XC);
      Y_px = ((touch.RawY() * TS_YM) + TS_YC);

      // Y_px correction. If your touch panel is accurate enough, it's okay to remove below.
      if ( 2048.0 < Y_px ) { 
        Y_px = Y_px + ((239 - Y_px) * 0.01673);
        } else if ( Y_px < 2048.0 ) {
          Y_px = Y_px - (Y_px * 0.02092);
          }
    }
    // Send touch data to ui_Main via queue
    tsLoc.X_Scr = X_px;
    tsLoc.Y_Scr = Y_px;
    xQueueSend(touchData, &tsLoc, 0);
    Serial3.println("[tsMgr] Queue has sent.");
   }
  }
