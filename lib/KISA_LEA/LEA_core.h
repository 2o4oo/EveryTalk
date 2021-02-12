//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of LEA Block Cipher on 8-bit AVR Processors (Balanced Optimization)                           //
// Copyright (C) 2015 KISA <http://www.kisa.or.kr>                                                              //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef LEA_CORE_H_
#define LEA_CORE_H_

typedef unsigned long DWORD;
typedef unsigned char BYTE;

#define ROR(W,i) (((W)>>(i)) | ((W)<<(32-(i))))
#define ROL(W,i) (((W)<<(i)) | ((W)>>(32-(i))))

#define DWORD_in(x)            (*(DWORD*)(x))
#define DWORD_out(x, v)        {*((DWORD*)(x)) = (v);}

void LEA_Key(const uint8_t* userkey, uint8_t* roundkey);
void LEA_Enc(const uint8_t* roundkey, uint8_t* data);
void LEA_Dec(const uint8_t* roundkey, uint8_t* data);


#endif /* LEA_CORE_H_ */

