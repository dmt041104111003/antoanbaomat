#include <iostream>
#include <fstream>
using namespace std;

long long habac(int a, int m, int n) {
    if (m == 0) return 1;
    if (m % 2 == 0) {
        long long half = habac(a, m / 2, n);
        return (half * half) % n;
    }
    return (a * habac(a, m - 1, n)) % n;
}


int main() {
    
    ifstream file("input.txt");
    int a,m,n;
    if (file >> a >> m >> n) {
        cout << "kq " << a << "^" << m << " mod " << n << " la: " << habac(a, m, n);
        file.close();
    } else return 1;
    return 0;
}
