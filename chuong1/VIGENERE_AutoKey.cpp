#include <iostream>
#include <fstream>
using namespace std;

string vigenere(string text, string key, bool encode) {
    string result = "";
    string full_key = key;
    for (int i = 0; i < text.length(); i++) {
        char c = (text[i] >= 'a' && text[i] <= 'z') ? text[i] - 32 : text[i];
        if (c >= 'A' && c <= 'Z') {
            char k = (i < full_key.length()) ? full_key[i] : result[i - key.length()];
            k = (k >= 'a' && k <= 'z') ? k - 32 : k; 
            int shift = encode ? (k - 'A') : -(k - 'A'); 
            result += (c - 'A' + shift + 26) % 26 + 'A';
            if (encode) full_key += c; 
        } else result += c;
    }
    return result;
}

int main() {
    string text, key;
    ifstream file("input_VIGENERE_AutoKey.txt");
    if (!file) return 1;
    getline(file, text);
    getline(file, key);
    file.close();
    string cipher = vigenere(text, key, true);
    string plain = vigenere(cipher, key, false);
    cout << "Ma hoa: " << cipher << endl << "Giai ma: " << plain << endl;
    return 0;
}

