#include <iostream>
#include <fstream>
#include "HangSo.h"
#include "String.cpp"
#include "MaHoa.cpp"
#include "GiaiMa.cpp"
using namespace std;
int main() {
    cout << "=== Reading input data ===\n";
    ifstream tep("input.txt");
    char ban_ro[33], khoa[33], bo_dem[256];
    ban_ro[0] = '\0';
    khoa[0] = '\0';
    
    if (tep.is_open()) {
        tep.getline(bo_dem, 256);
        cerr<<bo_dem<<endl;
        cerr<<ban_ro<<endl;
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
    
    cout << "=== Result (Encryption) ===\n";
    cout << "Ciphertext: " << trang_thai << "\n\n";

    cout << "=== AES Decryption ===\n";
    char ban_ma[33];
    sao_chep_chuoi(ban_ma, trang_thai);
    in_ma_tran(ban_ma, "Initial state (ciphertext)");

    cout << "Round 10:\n";
    cout << "  Round key K10: " << khoa_vong[10] << "\n";
    AddRoundKey(trang_thai_tam, ban_ma, khoa_vong[10]);
    sao_chep_chuoi(trang_thai, trang_thai_tam);
    in_ma_tran(trang_thai, "After AddRoundKey");

    InvShiftRows(trang_thai_tam, trang_thai);
    sao_chep_chuoi(trang_thai, trang_thai_tam);
    in_ma_tran(trang_thai, "After InvShiftRows");

    InvSubByte(trang_thai_tam, trang_thai);
    sao_chep_chuoi(trang_thai, trang_thai_tam);
    in_ma_tran(trang_thai, "After InvSubByte");

    for (int vong = 9; vong >= 1; vong--) {
        cout << "Round " << vong << ":\n";
        
        cout << "  Round key K" << vong << ": " << khoa_vong[vong] << "\n";
        AddRoundKey(trang_thai_tam, trang_thai, khoa_vong[vong]);
        sao_chep_chuoi(trang_thai, trang_thai_tam);
        in_ma_tran(trang_thai, "After AddRoundKey");
        
        InvMixColumns(trang_thai_tam, trang_thai);
        sao_chep_chuoi(trang_thai, trang_thai_tam);
        in_ma_tran(trang_thai, "After InvMixColumns");
        
        InvShiftRows(trang_thai_tam, trang_thai);
        sao_chep_chuoi(trang_thai, trang_thai_tam);
        in_ma_tran(trang_thai, "After InvShiftRows");
        
        InvSubByte(trang_thai_tam, trang_thai);
        sao_chep_chuoi(trang_thai, trang_thai_tam);
        in_ma_tran(trang_thai, "After InvSubByte");
    }

    cout << "Round 0:\n";
    cout << "  Round key K0: " << khoa_vong[0] << "\n";
    AddRoundKey(trang_thai_tam, trang_thai, khoa_vong[0]);
    sao_chep_chuoi(trang_thai, trang_thai_tam);
    in_ma_tran(trang_thai, "After AddRoundKey (Plaintext)");

    cout << "=== Result (Decryption) ===\n";
    cout << "Recovered Plaintext: " << trang_thai << "\n";
    return 0;
}
