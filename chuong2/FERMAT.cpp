#include <iostream>
#include <fstream>
using namespace std;

long long power_modulo(int a, int m, int n) {
    if (m == 0) return 1 % n;
    long long result = power_modulo(a, m / 2, n);
    result = (result * result) % n;
    if (m % 2 == 1)
        result = (result * a) % n;
    return result;
}

int main() {
    int a, m, n;
    ifstream file("input.txt");
    if (file >> a >> m >> n) {
        cout << "a^m mod n = " << power_modulo(a, m, n);
        file.close();
    } else return 1;
    return 0;
}
