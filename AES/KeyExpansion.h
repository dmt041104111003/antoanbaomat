#ifndef KEY_EXPANSION_H
#define KEY_EXPANSION_H

#include "HangSo.h"

void chia_khoa(char khoa[], char tu[][9]);
void rotWord(char ket_qua[], char tu[]);
int hex_thanh_so(char c);
unsigned int hex_thanh_gia_tri(char s[]);
void so_thanh_hex(char ket_qua[], unsigned int gia_tri, int do_rong);
bool kiem_tra_hex_hop_le(char s[]);
void mo_rong_khoa(char khoa[], char tu[][9], char khoa_vong[][33]);

#endif
