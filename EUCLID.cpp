#include <iostream>
#include <fstream>
using namespace std;

int mod_inverse(int a, int m, int& gcd) {
    int x = 1, y = 0, b = m, x1, y1;
    while (b) {
        x1 = y; y1 = x - (a / b) * y;
        x = x1; y = y1;
        gcd = b; b = a % b; a = gcd;
    }
    if (gcd != 1) return -1;
    return (x % m + m) % m;
}
 
int main() {
    int a, m, gcd;
    ifstream file("input.txt");
    if (file >> a >> m) {
        int inverse = mod_inverse(a, m, gcd);
        if (inverse != -1)
            cout << "nghich dao modulo " << a << " mod " << m << " la: " << inverse;
        else
            cout << "khong tinh duoc nghich dao modulo " << a << " mod " << m;
        file.close();
    } else return 1;
    return 0;
}
