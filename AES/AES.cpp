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
    char ban_ro[33], khoa[33];
    ban_ro[0] = '\0';
    khoa[0] = '\0';
    
    if (tep.is_open()) {
        tep.getline(ban_ro, 33);
        cout << "Plaintext: " << ban_ro << "\n";
        tep.getline(khoa, 33);
        cout << "Key: " << khoa << "\n\n";
        tep.close();
    } else return 1;

    cout << "=== Key Expansion ===\n";
    char tu[44][9], khoa_vong[11][33];
    mo_rong_khoa(khoa, tu, khoa_vong);
    
    cout << "=== AES Encryption ===\n";
    char trang_thai[33], luuTrangthai_tamthoi[33];
    sao_chep_chuoi(trang_thai, ban_ro);
    in_ma_tran(trang_thai, "Initial state (plaintext)");
    
    cout << "Round 0:\n";
    cout << "  Round key K0: " << khoa_vong[0] << "\n";
    AddRoundKey(luuTrangthai_tamthoi, trang_thai, khoa_vong[0]);
    sao_chep_chuoi(trang_thai, luuTrangthai_tamthoi);
    in_ma_tran(trang_thai, "After AddRoundKey");
    
    for (int vong = 1; vong <= 9; vong++) {
        cout << "Round " << vong << ":\n";
        
        subByte(luuTrangthai_tamthoi, trang_thai);
        sao_chep_chuoi(trang_thai, luuTrangthai_tamthoi);
        in_ma_tran(trang_thai, "After SubByte");
        
        ShiftRows(luuTrangthai_tamthoi, trang_thai);
        sao_chep_chuoi(trang_thai, luuTrangthai_tamthoi);
        in_ma_tran(trang_thai, "After ShiftRows");
        
        MixColumns(luuTrangthai_tamthoi, trang_thai);
        sao_chep_chuoi(trang_thai, luuTrangthai_tamthoi);
        in_ma_tran(trang_thai, "After MixColumns");
        
        cout << "  Round key K" << vong << ": " << khoa_vong[vong] << "\n";
        AddRoundKey(luuTrangthai_tamthoi, trang_thai, khoa_vong[vong]);
        sao_chep_chuoi(trang_thai, luuTrangthai_tamthoi);
        in_ma_tran(trang_thai, "After AddRoundKey");
    }
    
    cout << "Round 10:\n";
    subByte(luuTrangthai_tamthoi, trang_thai);
    sao_chep_chuoi(trang_thai, luuTrangthai_tamthoi);
    in_ma_tran(trang_thai, "After SubByte");
    
    ShiftRows(luuTrangthai_tamthoi, trang_thai);
    sao_chep_chuoi(trang_thai, luuTrangthai_tamthoi);
    in_ma_tran(trang_thai, "After ShiftRows");
    
    cout << "  Round key K10: " << khoa_vong[10] << "\n";
    AddRoundKey(luuTrangthai_tamthoi, trang_thai, khoa_vong[10]);
    sao_chep_chuoi(trang_thai, luuTrangthai_tamthoi);
    in_ma_tran(trang_thai, "After AddRoundKey (Ciphertext)");
    
    cout << "=== Result (Encryption) ===\n";
    cout << "Ciphertext: " << trang_thai << "\n\n";

    cout << "=== AES Decryption ===\n";
    char ban_ma[33];
    sao_chep_chuoi(ban_ma, trang_thai);
    in_ma_tran(ban_ma, "Initial state (ciphertext)");

    cout << "Round 10:\n";
    cout << "  Round key K10: " << khoa_vong[10] << "\n";
    AddRoundKey(luuTrangthai_tamthoi, ban_ma, khoa_vong[10]);
    sao_chep_chuoi(trang_thai, luuTrangthai_tamthoi);
    in_ma_tran(trang_thai, "After AddRoundKey");

    InvShiftRows(luuTrangthai_tamthoi, trang_thai);
    sao_chep_chuoi(trang_thai, luuTrangthai_tamthoi);
    in_ma_tran(trang_thai, "After InvShiftRows");

    InvSubByte(luuTrangthai_tamthoi, trang_thai);
    sao_chep_chuoi(trang_thai, luuTrangthai_tamthoi);
    in_ma_tran(trang_thai, "After InvSubByte");

    for (int vong = 9; vong >= 1; vong--) {
        cout << "Round " << vong << ":\n";
        
        cout << "  Round key K" << vong << ": " << khoa_vong[vong] << "\n";
        AddRoundKey(luuTrangthai_tamthoi, trang_thai, khoa_vong[vong]);
        sao_chep_chuoi(trang_thai, luuTrangthai_tamthoi);
        in_ma_tran(trang_thai, "After AddRoundKey");
        
        InvMixColumns(luuTrangthai_tamthoi, trang_thai);
        sao_chep_chuoi(trang_thai, luuTrangthai_tamthoi);
        in_ma_tran(trang_thai, "After InvMixColumns");
        
        InvShiftRows(luuTrangthai_tamthoi, trang_thai);
        sao_chep_chuoi(trang_thai, luuTrangthai_tamthoi);
        in_ma_tran(trang_thai, "After InvShiftRows");
        
        InvSubByte(luuTrangthai_tamthoi, trang_thai);
        sao_chep_chuoi(trang_thai, luuTrangthai_tamthoi);
        in_ma_tran(trang_thai, "After InvSubByte");
    }

    cout << "Round 0:\n";
    cout << "  Round key K0: " << khoa_vong[0] << "\n";
    AddRoundKey(luuTrangthai_tamthoi, trang_thai, khoa_vong[0]);
    sao_chep_chuoi(trang_thai, luuTrangthai_tamthoi);
    in_ma_tran(trang_thai, "After AddRoundKey (Plaintext)");

    cout << "=== Result (Decryption) ===\n";
    cout << "Recovered Plaintext: " << trang_thai << "\n";
    return 0;
}
