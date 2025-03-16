#include <bits/stdc++.h>
using namespace std;
string caesar(string tx, int s) {
    string str = "";
    for (char& c : tx) c = toupper(c);
    for (char c : tx) {
        if (isalpha(c)) {
            char ch = ((c - 'A' + s + 26) % 26) + 'A';
            str += ch;
        } else str += c;
    }
    return str;
}

int main() {
	string pt;
    int key;
    ifstream inputFile("../antoanbaomat/input1.txt");
    if (!inputFile.is_open()) cout << "err!";
    getline(inputFile, pt);
    inputFile >> key; 
    inputFile.close();
    cout << caesar(pt, key) << endl;
    return 0;
}
