#include <iostream>
#include <fstream>
using namespace std;

string monoCipher(string text, string key, bool encode) {
    string result = "";
    string k = key;
    for (char& c : k) if (c >= 'a' && c <= 'z') c -= 32;
    for (char c : text) {
        char ch = (c >= 'a' && c <= 'z') ? c - 32 : c;
        if (ch >= 'A' && ch <= 'Z') {
            if (encode) result += k[ch - 'A'];
            else {
                for (int i = 0; i < k.length(); i++) {
                    if (k[i] == ch) {
                        result += char(i + 'A');
                        ch = 0;
                        break;
                    }
                }
                if (ch != 0) result += '?';
            }
        } else result += ch;
    }
    return result;
}

int main() {
    string text, key;
    ifstream file("input_MaHoaChuDon.txt");
    if (!file) return 1;
    getline(file, text);
    getline(file, key);
    file.close();
    string cipher = monoCipher(text, key, true);
    string plain = monoCipher(cipher, key, false);
    cout << "Ma hoa: " << cipher << endl << "Giai ma: " << plain << endl;
    return 0;
}


