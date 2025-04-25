#include <iostream>
#include <fstream>
using namespace std;


void matran(char a[100][100], string banro, int m, int n) {
    int index = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = (index < banro.length()) ? banro[index++] : 0;
}

string hoanvi(string banro, string key, bool mahoa = true, int padding = 0) {
    int n = key.length();
    int m = banro.length() / n;
    char a[100][100] = {};
    int pos[100] = {};
    bool tick[100] = {};

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!tick[j] && key[j] == '1' + i) {
                pos[i] = j;
                tick[j] = true;
            }

    if (mahoa) {
        matran(a, banro, m, n);
        string banma;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (a[j][pos[i]])
                    banma += a[j][pos[i]];
        return banma;
    } else {
        string giaima;
        int index = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m && index < banro.length(); j++)
                a[j][pos[i]] = banro[index++];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (a[i][j])
                    giaima += a[i][j];
        if (padding > 0) {
		    string temp = "";
		    for (int i = 0; i < giaima.length() - padding; i++)
		        temp += giaima[i];
		    giaima = temp;
		}
        return giaima;
    }
}

int main() {
    ifstream file("input.txt");
    string key, banRo;
    getline(file, key);
    getline(file, banRo);
    file.close();
    int n = key.length();
    int padding = 0;
    while ((banRo.length() % n)!=0) {
        banRo += 'Z' - (n - banRo.length() % n) + 1;
        padding++;
    }
    string banMa = hoanvi(banRo, key, true); 
    string banGiaiMa = hoanvi(banMa, key, false, padding);
    cout << "Ban ma: " << banMa << endl;
    cout << "Ban giai ma: " << banGiaiMa << endl;

    return 0;
}

