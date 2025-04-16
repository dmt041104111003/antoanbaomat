#include <iostream>
#include <fstream>
using namespace std;

long long euler_power_mod(int a, int m, int n) {
    int phi_n = 1;
    for (int i = 2; i < n; ++i) {
        int x = i, y = n;
        while (y) {
            int temp = x % y;
            x = y;
            y = temp;
        }
        if (x == 1)
            ++phi_n;
    }
    m %= phi_n;
    long long result = 1;
    for (int i = 0; i < m; ++i)
        result = (result * a) % n;
    return result;
}

int main() {
    int a, m, n;
    ifstream file("input.txt");
    if (file >> a >> m >> n) {
        cout << "a^m mod n = " << euler_power_mod(a, m, n);
        file.close();
    } else return 1;
    return 0;
}
