//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of LEA Block Cipher on 8-bit AVR Processors (Balanced Optimization)                           //
// Copyright (C) 2015 KISA <http://www.kisa.or.kr>                                                              //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "LEA_core.h"
#include "LEA_core.c"

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  BYTE pbUserKey[16] = { 0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78, 0x87, 0x96, 0xa5, 0xb4, 0xc3, 0xd2, 0xe1, 0xf0 };
  BYTE pdwRoundKey[384] = { 0x0, };
  BYTE pbData[16] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
  int i;
  
  LEA_Key(pbUserKey, pdwRoundKey);
  LEA_Enc(pdwRoundKey,pbData);

  for(i=0;i<16;i++)
    Serial.print(pbData[i],HEX);
  Serial.println("");
  delay(1000);                                                                                                              
  
  LEA_Key(pbUserKey, pdwRoundKey);
  LEA_Dec(pdwRoundKey,pbData);
  for(i=0;i<16;i++)
    Serial.print(pbData[i],HEX);
  Serial.println("");
  delay(1000);                                                                                                              
}


