#include <iostream>
#include <fstream>
using namespace std;

int euler_phi(int n) {
    int result = n;
    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            result -= result / p;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

int main() {
    int n;
    ifstream file("input.txt");
    if (file >> n) {
        cout << "ket qua phi(" << n << ") la: " << euler_phi(n);
        file.close();
    } else return 1;
    return 0;
}
