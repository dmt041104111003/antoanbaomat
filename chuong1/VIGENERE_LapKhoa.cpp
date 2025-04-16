#include <iostream>
#include <fstream>
using namespace std;

string vigenere(string text, string key, bool encode = true) {
    string result = "";
    string key_upper = key;
    for (char& c : key_upper) 
        if (c >= 'a' && c <= 'z') c = c - ('a' - 'A');
    int key_len = key_upper.length();
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            char base = (c >= 'a') ? 'a' : 'A';
            if (base == 'a') c = c - ('a' - 'A');
            char k = key_upper[i % key_len];
            if (encode)
                c = ((c - 'A' + (k - 'A') + 26) % 26) + 'A';
            else
                c = ((c - k + 26) % 26) + 'A';
        }
        result += c;
    }
    return result;
}

int main() {
    string text, key;
    ifstream file("input_VIGENERE_LapKhoa.txt");
    if (!file) return 1;
    getline(file, text);
    getline(file, key);
    file.close();
    string ma_hoa = vigenere(text, key);
    cout << "Ma hoa: " << ma_hoa << "\n" << "Giai ma: " << vigenere(ma_hoa, key, false) << "\n";
    return 0;
}
