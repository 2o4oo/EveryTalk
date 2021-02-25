// Project EveryTalk - ui
static void ui_Main(void *params) {
  TSLocation tsLoc;
  
  for(;;) {
    xQueueReceive(touchData, &tsLoc, 0);
    if(tsLoc.X_Scr != NULL ) {
      Serial3.print("X:");
      Serial3.print(tsLoc.X_Scr);
      Serial3.print(", Y:");
      Serial3.print(tsLoc.Y_Scr);
      Serial3.print("\n");
    }
    
  }
}
