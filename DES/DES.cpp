#include <iostream>
#include "HangSo.h"

using namespace std;

string cat(string s, int dau, int dai) {
    string k = "";
    for (int i = dau; i < dau + dai && i < s.size(); i++) k += s[i];
    return k;
}

string hex_nhi(string s) {
    string k = "", khoa = "0123456789ABCDEF";
    string gia[16] = {"0000","0001","0010","0011","0100","0101","0110","0111",
                      "1000","1001","1010","1011","1100","1101","1110","1111"};
    for (char c : s)
        for (int j = 0; j < 16; j++)
            if (c == khoa[j]) k += gia[j];
    return k;
}

string nhi_hex(string s) {
    string k = "", gia = "0123456789ABCDEF";
    string khoa[16] = {"0000","0001","0010","0011","0100","0101","0110","0111",
                       "1000","1001","1010","1011","1100","1101","1110","1111"};
    for (int i = 0; i < s.size(); i += 4)
        for (int j = 0; j < 16; j++)
            if (cat(s, i, 4) == khoa[j]) k += gia[j];
    return k;
}

string hoan(string s, const int b[], int n) {
    string k = "";
    for (int i = 0; i < n; i++) k += s[b[i] - 1];
    return k;
}

string dich(string s, int lan) {
    while (lan--) s = cat(s, 1, 27) + s[0];
    return s;
}

string xor_chuoi(string a, string b) {
    string k = "";
    for (int i = 0; i < a.size(); i++) k += a[i] == b[i] ? "0" : "1";
    return k;
}

string sub_sbox(string x) {
    string op = "";
    for (int j = 0; j < 8; j++) {
        int hang = 2 * (x[j * 6] - '0') + (x[j * 6 + 5] - '0');
        int cot = 8 * (x[j * 6 + 1] - '0') + 4 * (x[j * 6 + 2] - '0') +
                 2 * (x[j * 6 + 3] - '0') + (x[j * 6 + 4] - '0');
        int g = s[j][hang][cot];
        op += char(g / 8 + '0'); g %= 8;
        op += char(g / 4 + '0'); g %= 4;
        op += char(g / 2 + '0'); g %= 2;
        op += char(g + '0');
    }
    return op;
}

string ma(string M, string khoa_v[16], string khoa_h[16]) {
    M = hex_nhi(M);
    M = hoan(M, IP, 64);
    cout << "Hoan dau: " << nhi_hex(M) << endl;

    string C = cat(M, 0, 32), D = cat(M, 32, 32);
    cout << "Tach: L0=" << nhi_hex(C) << " R0=" << nhi_hex(D) << endl;

    for (int vong = 0; vong < 16; vong++) {
        cout << "Vong " << vong + 1 << ":\n";
        cout << "  Subkey (K" << vong + 1 << "): " << khoa_h[vong] << endl;

        string mo_rong_nuaphai = hoan(D, E, 48);
        cout << "  E" << vong + 1 << " (Expansion): " << nhi_hex(mo_rong_nuaphai) << endl;

        string x = xor_chuoi(khoa_v[vong], mo_rong_nuaphai);
        cout << "  XOR(E" << vong + 1 << ",K" << vong + 1 << "): " << nhi_hex(x) << endl;

        string op = sub_sbox(x);
        cout << "  S-box: " << nhi_hex(op) << endl;

        op = hoan(op, thang, 32);
        cout << "  P(S-box): " << nhi_hex(op) << endl;

        x = xor_chuoi(op, C);
        cout << "  XOR(P,L" << vong + 1 << "): " << nhi_hex(x) << endl;

        C = x;
        if (vong < 15) {
            string t = C;
            C = D;
            D = t;
        }

        cout << "  L" << vong + 1 << ": " << nhi_hex(C) << " R" << vong + 1 << ": " << nhi_hex(D) << endl;
    }

    string hop = C + D;
    return nhi_hex(hoan(hop, IP_1, 64));
}

string giai_ma(string mahoa, string khoa_v[16], string khoa_h[16]) {
    mahoa = hex_nhi(mahoa);
    mahoa = hoan(mahoa, IP, 64);
    cout << "Hoan dau: " << nhi_hex(mahoa) << endl;

    string C = cat(mahoa, 0, 32), D = cat(mahoa, 32, 32);
    cout << "Tach: L0=" << nhi_hex(C) << " R0=" << nhi_hex(D) << endl;

    for (int vong = 0; vong < 16; vong++) {
        cout << "Vong " << vong + 1 << ":\n";
        cout << "  Subkey (K" << 16 - vong << "): " << khoa_h[15 - vong] << endl;

        string mo_rong_nuaphai = hoan(D, E, 48);
        cout << "  E" << vong + 1 << " (Expansion): " << nhi_hex(mo_rong_nuaphai) << endl;

        string x = xor_chuoi(khoa_v[15 - vong], mo_rong_nuaphai);
        cout << "  XOR(E" << vong + 1 << ",K" << 16 - vong << "): " << nhi_hex(x) << endl;

        string op = sub_sbox(x);
        cout << "  S-box: " << nhi_hex(op) << endl;

        op = hoan(op, thang, 32);
        cout << "  P(S-box): " << nhi_hex(op) << endl;

        x = xor_chuoi(op, C);
        cout << "  XOR(P,L" << vong + 1 << "): " << nhi_hex(x) << endl;

        C = x;
        if (vong < 15) {
            string t = C;
            C = D;
            D = t;
        }

        cout << "  L" << vong + 1 << ": " << nhi_hex(C) << " R" << vong + 1 << ": " << nhi_hex(D) << endl;
    }

    string hop = C + D;
    return nhi_hex(hoan(hop, IP_1, 64));
}

int main() {
    string M = "FF1C9CA3596B7D48", khoa = "3FF81CDA5F417784";
    khoa = hex_nhi(khoa);

    khoa = hoan(khoa, PC_1, 56);

    string C = cat(khoa, 0, 28), D = cat(khoa, 28, 28);
    string khoa_bin[16], khoa_hex[16];
    for (int i = 0; i < 16; i++) {
        C = dich(C, vong_dich[i]);
        D = dich(D, vong_dich[i]);
        khoa_bin[i] = hoan(C + D, PC_2, 48);
        khoa_hex[i] = nhi_hex(khoa_bin[i]);
        cerr<<khoa_hex[i]<<endl;
    }
    cout << "\nMa hoa:\n";
    string mahoa = ma(M, khoa_bin, khoa_hex);
    cout << "Ma: " << mahoa << endl;

    cout << "\nGiai ma:\n";
    string goc = giai_ma(mahoa, khoa_bin, khoa_hex);
    cout << "Goc: " << goc << endl;

    return 0;
}
