#include <iostream>
#include "String.h"
#include "MaHoa.h"
using namespace std;
void in_ma_tran(char s[], const char ten[]) {
    cout << ten << ":\n";
    for (int hang = 0; hang < 4; hang++) {
        cout << "  [ ";
        for (int cot = 0; cot < 4; cot++) {
            char byte[3];
            cat_chuoi_con(byte, s, (cot * 8 + hang * 2), 2);
            cout << byte;
            if (cot < 3) cout << " ";
        }
        cout << " ]\n";
    }
    cout << "  Hex: " << s << "\n\n";
}

void subByte(char ket_qua[], char chuoi_goc[]) {
    ket_qua[0] = '\0';
    for (int i = 0; i < dem_do_dai_chuoi(chuoi_goc); i += 2) {
        int hang = hex_thanh_so(chuoi_goc[i]);
        int cot = hex_thanh_so(chuoi_goc[i + 1]);
        noi_chuoi(ket_qua, s_box[hang][cot]);
    }
}

void ShiftRows(char ket_qua[], char chuoi_goc[]) {
    int chi_so[16] = {0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12, 1, 6, 11};
    ket_qua[0] = '\0';
    for (int i = 0; i < 16; i++) {
        char luukq_tamthoi[3];
        cat_chuoi_con(luukq_tamthoi, chuoi_goc, chi_so[i] * 2, 2);
        noi_chuoi(ket_qua, luukq_tamthoi);
    }
}

void AddRoundKey(char ket_qua[], char hex1[], char hex2[]) {
    int do_dai = dem_do_dai_chuoi(hex1);
    if (do_dai != dem_do_dai_chuoi(hex2) || do_dai % 8 != 0 || 
        !kiem_tra_hex_hop_le(hex1) || !kiem_tra_hex_hop_le(hex2)) {
        cout << "hex k hop le!\n";
        return;
    }
    ket_qua[0] = '\0';
    for (int i = 0; i < do_dai; i += 8) {
        char tamthoi_hex1[9], tamthoi_hex2[9], luukq_xorTamthoi[9];
        cat_chuoi_con(tamthoi_hex1, hex1, i, 8);
        cat_chuoi_con(tamthoi_hex2, hex2, i, 8);
        so_thanh_hex(luukq_xorTamthoi, hex_thanh_gia_tri(tamthoi_hex1) ^ hex_thanh_gia_tri(tamthoi_hex2), 8);
        noi_chuoi(ket_qua, luukq_xorTamthoi);
    }
}

void MixColumns(char ket_qua[], char chuoi_goc[]) {
    char ma_tran[16][3] = {
        {"02"}, {"03"}, {"01"}, {"01"},
        {"01"}, {"02"}, {"03"}, {"01"},
        {"01"}, {"01"}, {"02"}, {"03"},
        {"03"}, {"01"}, {"01"}, {"02"}
    };
    char ma_tran_trang_thai[16][3];
    int thu_tu[16] = {0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15};
    for (int i = 0; i < 16; i++) cat_chuoi_con(ma_tran_trang_thai[i], chuoi_goc, thu_tu[i] * 2, 2);
    
    ket_qua[0] = '\0';
    for (int i = 0; i < 16; i++) {
        int hang = thu_tu[i] / 4;
        int cot = thu_tu[i] % 4;
        unsigned int luukq_xor = 0;
        for (int j = 0; j < 4; j++) luukq_xor ^= nhan_hex(ma_tran[hang * 4 + j], ma_tran_trang_thai[4 * j + cot]);
        char hex[3];
        so_thanh_hex(hex, luukq_xor, 2);
        noi_chuoi(ket_qua, hex);
    }
}

unsigned int nhan_hex(char hex1[], char hex2[]) {
    unsigned int mod = 283;
    unsigned int a = hex_thanh_gia_tri(hex1);
    unsigned int b = hex_thanh_gia_tri(hex2);
    unsigned int ket_qua = 0;
    
    for (int i = 0; i < 8; i++) if ((a & (1 << i))!=0) ket_qua ^= (b << i);
    while (ket_qua >= 256) {
        int solan_dichbit_timBacMAX = 0;
        unsigned int tam = ket_qua;
        while (tam >= 256) {
            tam >>= 1;
            solan_dichbit_timBacMAX++;
        }
        ket_qua ^= (mod << (solan_dichbit_timBacMAX - 1));
    }
    return ket_qua;
}

int hex_thanh_so(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

unsigned int hex_thanh_gia_tri(char s[]) {
    unsigned int ket_qua = 0;
    for (int i = 0; s[i] != '\0'; i++) ket_qua = hex_thanh_so(s[i])+ket_qua * 16;
    return ket_qua;
}

void so_thanh_hex(char ket_qua[], unsigned int gia_tri, int do_rong) {
    char luu_hex_tamthoi[32];
    int i = 0;
    if (gia_tri == 0) for (i = 0; i < do_rong; i++) luu_hex_tamthoi[i] = '0';
    else {
        while (gia_tri > 0) {
            int chu_so = gia_tri % 16;
            if (chu_so < 10) luu_hex_tamthoi[i] = chu_so + '0';
            else luu_hex_tamthoi[i] = chu_so - 10 + 'A';
            gia_tri /=16;
            i++;
        }
        while (i < do_rong) {
            luu_hex_tamthoi[i] = '0';
            i++;
        }
    }
    for (int j = 0; j < do_rong; j++) ket_qua[j] = luu_hex_tamthoi[do_rong - 1 - j];
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

void chia_khoa(char key[], char word[][9]) {
    for (int i = 0; i < 4; i++) cat_chuoi_con(word[i], key, i * 8, 8);
}

void rotWord(char ket_qua[], char word[]) {
    char luuketqua_tamthoi_xorRcon[9];
    cat_chuoi_con(luuketqua_tamthoi_xorRcon, word, 2, 6);
    cat_chuoi_con(ket_qua, word, 0, 2);
    noi_chuoi(luuketqua_tamthoi_xorRcon, ket_qua);
    sao_chep_chuoi(ket_qua, luuketqua_tamthoi_xorRcon);
}


void mo_rong_khoa(char key[], char word[][9], char khoa_vong[][33]) {
    chia_khoa(key, word);
    
    cout << "Initial words (w[0] to w[3]):\n";
    for (int i = 0; i < 4; i++) cout << "  w[" << i << "] = " << word[i] << "\n";
    khoa_vong[0][0] = '\0';
    for (int i = 0; i < 4; i++) noi_chuoi(khoa_vong[0], word[i]);
    cout << "Round key 0 (K0): " << khoa_vong[0] << "\n\n";
    
    for (int vong = 1; vong <= 10; vong++) {
        cout << "Round " << vong << ":\n";
        char luuketqua_tamthoi_rotWord[9], luuketqua_tamthoi_subByte[9], luuketqua_tamthoi_xorRcon[9];

        rotWord(luuketqua_tamthoi_rotWord, word[vong * 4 - 1]);
        cout << "  RotWord w[" << vong * 4 - 1 << "] (" << word[vong * 4 - 1] << "): " << luuketqua_tamthoi_rotWord << "\n";
        
        subByte(luuketqua_tamthoi_subByte, luuketqua_tamthoi_rotWord);
        cout << "  SubWord (S-box): " << luuketqua_tamthoi_subByte << "\n";
        
        AddRoundKey(luuketqua_tamthoi_xorRcon, luuketqua_tamthoi_subByte, r_con[vong]);
        cout << "  XOR with Rcon[" << vong << "] (" << r_con[vong] << "): " << luuketqua_tamthoi_xorRcon << "\n";
        
        AddRoundKey(word[vong * 4], word[vong * 4 - 4], luuketqua_tamthoi_xorRcon);
        cout << "  w[" << vong * 4 << "] = w[" << vong * 4 - 4 << "] (" << word[vong * 4 - 4] << ") XOR temp: " << word[vong * 4] << "\n";
        
        for (int j = 1; j < 4; j++) {
            AddRoundKey(word[vong * 4 + j], word[vong * 4 + j - 1], word[vong * 4 + j - 4]);
            cout << "  w[" << vong * 4 + j << "] = w[" << vong * 4 + j - 1 << "] (" << word[vong * 4 + j - 1] 
                 << ") XOR w[" << vong * 4 + j - 4 << "] (" << word[vong * 4 + j - 4] << "): " << word[vong * 4 + j] << "\n";
        }
        
        khoa_vong[vong][0] = '\0';
        for (int j = 0; j < 4; j++) noi_chuoi(khoa_vong[vong], word[vong * 4 + j]);
        cout << "  Round key " << vong << " (K" << vong << "): " << khoa_vong[vong] << "\n\n";
    }
}
