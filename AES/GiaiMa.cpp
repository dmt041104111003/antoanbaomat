#include <iostream>
#include "String.h"
#include "GiaiMa.h"
using namespace std;

void InvShiftRows(char ket_qua[], char nguon[]) {
    int chi_so[16] = {0, 13, 10, 7, 4, 1, 14, 11, 8, 5, 2, 15, 12, 9, 6, 3};
    ket_qua[0] = '\0';
    for (int i = 0; i < 16; i++) {
        char tam[3];
        cat_chuoi_con(tam, nguon, chi_so[i] * 2, 2);
        noi_chuoi(ket_qua, tam);
    }
}

void InvSubByte(char ket_qua[], char nguon[]) {
    ket_qua[0] = '\0';
    for (int i = 0; i < dem_do_dai_chuoi(nguon); i += 2) {
        int hang = hex_thanh_so(nguon[i]);
        int cot = hex_thanh_so(nguon[i + 1]);
        noi_chuoi(ket_qua, inv_s_box[hang][cot]);
    }
}

void InvMixColumns(char ket_qua[], char nguon[]) {
    char ma_tran[16][3] = {
        {"0E"}, {"0B"}, {"0D"}, {"09"},
        {"09"}, {"0E"}, {"0B"}, {"0D"},
        {"0D"}, {"09"}, {"0E"}, {"0B"},
        {"0B"}, {"0D"}, {"09"}, {"0E"}
    };
    char ma_tran_trang_thai[16][3];
    int thu_tu[16] = {0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15};
    for (int i = 0; i < 16; i++) cat_chuoi_con(ma_tran_trang_thai[i], nguon, thu_tu[i] * 2, 2);
    
    ket_qua[0] = '\0';
    for (int i = 0; i < 16; i++) {
        int hang = thu_tu[i] / 4;
        int cot = thu_tu[i] % 4;
        unsigned int tam = 0;
        for (int j = 0; j < 4; j++) tam ^= nhan_hex(ma_tran[hang * 4 + j], ma_tran_trang_thai[4 * j + cot]);
        char hex[3];
        so_thanh_hex(hex, tam, 2);
        noi_chuoi(ket_qua, hex);
    }
}
