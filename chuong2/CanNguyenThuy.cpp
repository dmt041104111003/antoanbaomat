#include <iostream>
#include <fstream>
using namespace std;

bool is_primitive_root(int a, int n) {
    // Ki?m tra UCLN(a, n) = 1
    int x = a, y = n;
    while (y) {
        int tmp = x % y;
        x = y;
        y = tmp;
    }
    if (x != 1) return false;

    // Tìm u?c nguyên t? c?a phi = n-1
    int phi = n - 1, m = phi, f[5], c = 0;
    for (int i = 2; i <= m; i++)
        if (m % i == 0) {
            f[c++] = i;
            while (m % i == 0) m /= i;
        }

    // Ki?m tra a^(phi/p) != 1
    for (int i = 0; i < c; i++) {
        long long r = 1, b = a;
        int e = phi / f[i];
        while (e--) r = (r * b) % n;
        if (r == 1) return false;
    }
    return true;
}

int main() {
    int a, n;
    ifstream file("input.txt");
    file >> a >> n;
    cout << a << (is_primitive_root(a, n) ? " la can nguyen thuy cua " : " khong la can nguyen thuy cua ") << n;
    return 0;
}
