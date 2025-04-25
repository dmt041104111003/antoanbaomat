#ifndef AES_H
#define AES_H

#include "HangSo.h"
void ShiftRows(char ket_qua[], char nguon[]);
void rotWord(char ket_qua[], char tu[]);
void subByte(char ket_qua[], char nguon[]);
void AddRoundKey(char ket_qua[], char hex1[], char hex2[]);

#endif
