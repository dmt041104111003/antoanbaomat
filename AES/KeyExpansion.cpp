#include <iostream>
#include "KeyExpansion.h"
#include "String.h"
using namespace std;

int hex_thanh_so(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

unsigned int hex_thanh_gia_tri(char s[]) {
    unsigned int ket_qua = 0;
    for (int i = 0; s[i] != '\0'; i++) ket_qua = ket_qua * 16 + hex_thanh_so(s[i]);
    return ket_qua;
}

void so_thanh_hex(char ket_qua[], unsigned int gia_tri, int do_rong) {
    char tam[32];
    int i = 0;
    if (gia_tri == 0) for (i = 0; i < do_rong; i++) tam[i] = '0';
    else {
        while (gia_tri > 0) {
            int chu_so = gia_tri % 16;
            if (chu_so < 10) tam[i] = chu_so + '0';
            else tam[i] = chu_so - 10 + 'A';
            gia_tri = gia_tri / 16;
            i++;
        }
        while (i < do_rong) {
            tam[i] = '0';
            i++;
        }
    }
    for (int j = 0; j < do_rong; j++) ket_qua[j] = tam[do_rong - 1 - j];
    ket_qua[do_rong] = '\0';
}

bool kiem_tra_hex_hop_le(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (!((s[i] >= '0' && s[i] <= '9') || 
              (s[i] >= 'A' && s[i] <= 'F') || 
              (s[i] >= 'a' && s[i] <= 'f'))) {
            return false;
        }
    }
    return true;
}


void chia_khoa(char khoa[], char tu[][9]) {
    for (int i = 0; i < 4; i++) cat_chuoi_con(tu[i], khoa, i * 8, 8);
}

void rotWord(char ket_qua[], char tu[]) {
    char tam[9];
    cat_chuoi_con(tam, tu, 2, 6);
    cat_chuoi_con(ket_qua, tu, 0, 2);
    noi_chuoi(tam, ket_qua);
    sao_chep_chuoi(ket_qua, tam);
}

void mo_rong_khoa(char khoa[], char tu[][9], char khoa_vong[][33]) {
    chia_khoa(khoa, tu);
    
    cout << "Initial words (w[0] to w[3]):\n";
    for (int i = 0; i < 4; i++) cout << "  w[" << i << "] = " << tu[i] << "\n";
    khoa_vong[0][0] = '\0';
    for (int i = 0; i < 4; i++) noi_chuoi(khoa_vong[0], tu[i]);
    cout << "Round key 0 (K0): " << khoa_vong[0] << "\n\n";
    
    for (int vong = 1; vong <= 10; vong++) {
        cout << "Round " << vong << ":\n";
        char tu_xoay[9], tu_thay[9], tam[9];
        
        rotWord(tu_xoay, tu[vong * 4 - 1]);
        cout << "  RotWord w[" << vong * 4 - 1 << "] (" << tu[vong * 4 - 1] << "): " << tu_xoay << "\n";
        
        subByte(tu_thay, tu_xoay);
        cout << "  SubByte (S-box): " << tu_thay << "\n";
        
        AddRoundKey(tam, tu_thay, r_con[vong]);
        cout << "  XOR with Rcon[" << vong << "] (" << r_con[vong] << "): " << tam << "\n";
        
        AddRoundKey(tu[vong * 4], tu[vong * 4 - 4], tam);
        cout << "  w[" << vong * 4 << "] = w[" << vong * 4 - 4 << "] (" << tu[vong * 4 - 4] << ") XOR temp: " << tu[vong * 4] << "\n";
        
        for (int j = 1; j < 4; j++) {
            AddRoundKey(tu[vong * 4 + j], tu[vong * 4 + j - 1], tu[vong * 4 + j - 4]);
            cout << "  w[" << vong * 4 + j << "] = w[" << vong * 4 + j - 1 << "] (" << tu[vong * 4 + j - 1] 
                 << ") XOR w[" << vong * 4 + j - 4 << "] (" << tu[vong * 4 + j - 4] << "): " << tu[vong * 4 + j] << "\n";
        }
        
        khoa_vong[vong][0] = '\0';
        for (int j = 0; j < 4; j++) noi_chuoi(khoa_vong[vong], tu[vong * 4 + j]);
        cout << "  Round key " << vong << " (K" << vong << "): " << khoa_vong[vong] << "\n\n";
    }
}
