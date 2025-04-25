#ifndef MA_HOA_H
#define MA_HOA_H

#include "HangSo.h"
void in_ma_tran(char s[],const char ten[]);
void subByte(char ket_qua[], char nguon[]);
void ShiftRows(char ket_qua[], char nguon[]);
void AddRoundKey(char ket_qua[], char hex1[], char hex2[]);
void MixColumns(char ket_qua[], char nguon[]);
unsigned int nhan_hex(char hex1[], char hex2[]);
int hex_thanh_so(char c);
unsigned int hex_thanh_gia_tri(char s[]);
void so_thanh_hex(char ket_qua[], unsigned int gia_tri, int do_rong);
bool kiem_tra_hex_hop_le(char s[]);
void chia_khoa(char khoa[], char tu[][9]);
void rotWord(char ket_qua[], char tu[]);
void mo_rong_khoa(char khoa[], char tu[][9], char khoa_vong[][33]);
#endif
