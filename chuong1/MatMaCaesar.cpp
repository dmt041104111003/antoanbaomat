#include <iostream>
#include <fstream>
using namespace std;

string caesar(string text, int k, bool encode = true) {
    string result = "";
    if (!encode) k = -k;
    for (char c : text) {
        if (c >= 'A' && c <= 'Z') 
            c = ((c - 'A' + k + 26) % 26) + 'A';
        else if (c >= 'a' && c <= 'z') 
            c = ((c - 'a' + k + 26) % 26) + 'a';
        result += c;
    }
    return result;
}

int main() {
    string text; int k;
    ifstream file("input_caesar.txt");
    if (!file) return 1;
    getline(file, text);
    file >> k; file.close();
    string ma_hoa = caesar(text, k);
    cout << "Ma hoa: " << ma_hoa << "\n" << "Giai ma: " << caesar(ma_hoa, k, false) << "\n";
    return 0;
}
