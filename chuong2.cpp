#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ex exception
bool readf(string filename, int& a, int& m, int& n) {
    ifstream file(filename);
    if (!file.is_open()) return false;
    try {
        string line;
        getline(file, line);
        stringstream ss(line);
        if (!(ss >> a >> m >> n)) return false;
        file.close();
        return true;
    }
    catch (const ex& e) {
        file.close();
        return false;
    }
}

ll mod(ll a, ll m, ll n) {
    if (m == 0) return 1;
    else if (m % 2 == 0) {
        ll hp = mod(a, m / 2, n);
        return (hp*hp) % n;
    }
    else return (a * mod(a, m - 1, n)) % n;
    
}

int main() {
    string input_filename = "../antoanbaomat/input.txt";
    int a, m, n;
    if (readf(input_filename, a, m, n)) {
        ll res = mod(a, m, n);
        cout << a << "^" << m << " mod " << n << " la: " << res << endl;
    }
    else cout << "err";
    return 0;
}
