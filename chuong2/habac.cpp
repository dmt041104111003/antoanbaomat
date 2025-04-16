#include <iostream>
#include <fstream>
using namespace std;

long long mod_exp(int a, int m, int n) {
    if (m == 0) return 1;
    if (m % 2 == 0) {
        long long half = mod_exp(a, m / 2, n);
        return (half * half) % n;
    }
    return (a * mod_exp(a, m - 1, n)) % n;
}

int main() {
    int a, m, n;
    ifstream file("input.txt");
    if (file >> a >> m >> n) {
        cout << "kq " << a << "^" << m << " mod " << n << " la: " << mod_exp(a, m, n);
        file.close();
    } else return 1;
    return 0;
}
