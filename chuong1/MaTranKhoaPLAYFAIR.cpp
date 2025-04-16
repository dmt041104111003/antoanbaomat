#include <iostream>
#include <fstream>
using namespace std;

string playfair(string text, string key) {
    char table[5][5] = {0};
    bool used[26] = {0};
    int row = 0, col = 0;

    for (char c : key) {
        c = toupper(c);
        if (c == 'J') c = 'I';
        if (c >= 'A' && c <= 'Z' && !used[c - 'A']) {
            table[row][col] = c;
            used[c - 'A'] = 1;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue;
        if (!used[c - 'A']) {
            table[row][col] = c;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    string prepared;
    for (char c : text) {
        c = toupper(c);
        if (c == 'J') c = 'I';
        if (c >= 'A' && c <= 'Z') prepared += c;
    }

    string pairs;
    for (int i = 0; i < prepared.size(); i++) {
        pairs += prepared[i];
        if (i + 1 < prepared.size() && prepared[i] != prepared[i + 1]) {
            pairs += prepared[++i];
        } else {
            pairs += 'X';
        }
    }

    string cipher;
    for (int i = 0; i < pairs.size(); i += 2) {
        char a = pairs[i], b = pairs[i + 1];
        int r1, c1, r2, c2;

        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                if (table[r][c] == a) {
                    r1 = r; c1 = c;
                }
                if (table[r][c] == b) {
                    r2 = r; c2 = c;
                }
            }
        }

        if (r1 == r2) {
            cipher += table[r1][(c1 + 1) % 5];
            cipher += table[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            cipher += table[(r1 + 1) % 5][c1];
            cipher += table[(r2 + 1) % 5][c2];
        } else {
            cipher += table[r1][c2];
            cipher += table[r2][c1];
        }
    }

    return cipher;
}

int main() {
    string key, text;
    ifstream file("input_PLAYFAIR.txt");
    if (!file) return 1;
    getline(file, key);
    getline(file, text);
    file.close();
    string cipher = playfair(text, key);
    cout << "Ma hoa: " << cipher << endl;
    return 0;
}
