#include <iostream>
#include <fstream>
using namespace std;

long long mod_exp(int a, int k, int n) {
    long long b = 1;
    for (int i = 0; i < k; ++i)
        b = (b * a) % n;
    return b;
}

int main() {
    int a, k, n;
    ifstream file("input.txt");
    if (file >> a >> k >> n) {
        cout << "ket qua " << a << "^" << k << " mod " << n << " la: " << mod_exp(a, k, n);
        file.close();
    } else return 1;
    return 0;
}
