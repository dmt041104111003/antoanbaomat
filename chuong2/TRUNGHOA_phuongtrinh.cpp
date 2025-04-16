#include <iostream>
#include <fstream>
using namespace std;

long long chinese_remainder(int m1, int m2, int m3, int a1, int a2, int a3) {
    long long M = (long long)m1 * m2 * m3;
    long long M1 = M / m1, M2 = M / m2, M3 = M / m3;

    auto mod_inverse = [](int a, int m) {
        int x = 1, y = 0, b = m, x1, y1;
        while (b) {
            x1 = y; y1 = x - (a / b) * y;
            x = x1; y = y1;
            int gcd = b; b = a % b; a = gcd;
        }
        return (x % m + m) % m;
    };

    long long inv1 = mod_inverse(M1, m1);
    long long inv2 = mod_inverse(M2, m2);
    long long inv3 = mod_inverse(M3, m3);

    return (a1 * M1 * inv1 + a2 * M2 * inv2 + a3 * M3 * inv3) % M;
}

int main() {
    int m1, m2, m3, a1, a2, a3;
    ifstream file("input.txt");
    if (file >> m1 >> m2 >> m3 >> a1 >> a2 >> a3) {
        cout << "ket qua sau khi giai he pt x= : " << chinese_remainder(m1, m2, m3, a1, a2, a3);
        file.close();
    } else return 1;
    return 0;
}
