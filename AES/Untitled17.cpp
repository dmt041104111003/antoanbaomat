#include <iostream>
#include <fstream>
#include "HangSo.h"
#include "String.cpp"
#include "KeyExpansion.cpp"
using namespace std;

void in_ma_tran(char s[], char ten[]) {
    cout << ten << ":\n";
    for (int hang = 0; hang < 4; hang++) {
        cout << "  [ ";
        for (int cot = 0; cot < 4; cot++) {
            char byte[3];
            cat_chuoi_con(byte, s, hang * 8 + cot * 2, 2);
            cout << byte;
            if (cot < 3) cout << " ";
        }
        cout << " ]\n";
    }
    cout << "  Hex: " << s << "\n\n";
}

unsigned int nhan_hex(char hex1[], char hex2[]) {
    unsigned int mod = 0x11b;
    unsigned int a = hex_thanh_gia_tri(hex1);
    unsigned int b = hex_thanh_gia_tri(hex2);
    unsigned int ket_qua = 0;
    
    for (int i = 0; i < 8; i++) if (a & (1 << i)) ket_qua ^= (b << i);
    while (ket_qua >= 0x100) {
        int dich = 0;
        unsigned int tam = ket_qua;
        while (tam >= 0x100) {
            tam >>= 1;
            dich++;
        }
        ket_qua ^= (mod << (dich - 1));
    }
    return ket_qua;
}

void MixColumns(char ket_qua[], char nguon[]) {
    char ma_tran[16][3] = {
        {"02"}, {"03"}, {"01"}, {"01"},
        {"01"}, {"02"}, {"03"}, {"01"},
        {"01"}, {"01"}, {"02"}, {"03"},
        {"03"}, {"01"}, {"01"}, {"02"}
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

int main() {
    cout << "=== Reading input data ===\n";
    ifstream tep("input.txt");
    char ban_ro[33], khoa[33], bo_dem[256];
    ban_ro[0] = '\0';
    khoa[0] = '\0';
    
    if (tep.is_open()) {
        tep.getline(bo_dem, 256);
        xoa_khoang_trang(ban_ro, bo_dem);
        cout << "Plaintext: " << ban_ro << "\n";
        
        tep.getline(bo_dem, 256);
        xoa_khoang_trang(khoa, bo_dem);
        cout << "Key: " << khoa << "\n\n";
        tep.close();
    } else return 1;

    cout << "=== Key Expansion ===\n";
    char tu[44][9], khoa_vong[11][33];
    mo_rong_khoa(khoa, tu, khoa_vong);

    cout << "=== AES Encryption ===\n";
    char trang_thai[33], trang_thai_tam[33];
    sao_chep_chuoi(trang_thai, ban_ro);
    in_ma_tran(trang_thai, "Initial state (plaintext)");
    
    cout << "Round 0:\n";
    cout << "  Round key K0: " << khoa_vong[0] << "\n";
    AddRoundKey(trang_thai_tam, trang_thai, khoa_vong[0]);
    sao_chep_chuoi(trang_thai, trang_thai_tam);
    in_ma_tran(trang_thai, "After AddRoundKey");
    
    for (int vong = 1; vong <= 9; vong++) {
        cout << "Round " << vong << ":\n";
        
        subByte(trang_thai_tam, trang_thai);
        sao_chep_chuoi(trang_thai, trang_thai_tam);
        in_ma_tran(trang_thai, "After SubByte");
        
        ShiftRows(trang_thai_tam, trang_thai);
        sao_chep_chuoi(trang_thai, trang_thai_tam);
        in_ma_tran(trang_thai, "After ShiftRows");
        
        MixColumns(trang_thai_tam, trang_thai);
        sao_chep_chuoi(trang_thai, trang_thai_tam);
        in_ma_tran(trang_thai, "After MixColumns");
        
        cout << "  Round key K" << vong << ": " << khoa_vong[vong] << "\n";
        AddRoundKey(trang_thai_tam, trang_thai, khoa_vong[vong]);
        sao_chep_chuoi(trang_thai, trang_thai_tam);
        in_ma_tran(trang_thai, "After AddRoundKey");
    }
    
    cout << "Round 10:\n";
    subByte(trang_thai_tam, trang_thai);
    sao_chep_chuoi(trang_thai, trang_thai_tam);
    in_ma_tran(trang_thai, "After SubByte");
    
    ShiftRows(trang_thai_tam, trang_thai);
    sao_chep_chuoi(trang_thai, trang_thai_tam);
    in_ma_tran(trang_thai, "After ShiftRows");
    
    cout << "  Round key K10: " << khoa_vong[10] << "\n";
    AddRoundKey(trang_thai_tam, trang_thai, khoa_vong[10]);
    sao_chep_chuoi(trang_thai, trang_thai_tam);
    in_ma_tran(trang_thai, "After AddRoundKey (Ciphertext)");
    
    cout << "=== Result ===\n";
    cout << "Ciphertext: " << trang_thai << "\n";
    return 0;
}
