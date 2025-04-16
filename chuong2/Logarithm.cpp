#include <iostream>
#include <fstream>
using namespace std;

long long logarit_RoiRac(long long a, long long b, long long n) {
    long long result = 1, k = 0;
    while (k < n) {
        if (result % n == b) return k;
        result = (result * a) % n;
        k++;
    }
    return -1;
}

int main() {
    long long a, b, n;
    
    ifstream file("input.txt");
    if (file >> a >> b >> n) {
        long long k = logarit_RoiRac(a, b, n);
        if (k == -1)
            cout << "Khong tim thay logarithm roi rac.\n";
        else
            cout << "Logarithm roi rac la: " << k << "\n";
        file.close();
    } else {
        cout << "Loi doc file.\n";
        return 1;
    }
    
    return 0;
}
