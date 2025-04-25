#include <iostream>
#include <fstream>

using namespace std;
long long habac(long long a, long long m, long long n) {
    if (m == 0) return 1;
    if (m % 2 == 0) {
        long long half = habac(a, m / 2, n);
        return (half * half) % n;
    }
    return (a * habac(a, m - 1, n)) % n;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cout << "Loi: Khong the mo file input" << endl;
        return 1;
    }

    long long q, a, xA, k, M;
    if (!(inputFile >> q >> a >> xA >> k >> M)) {
        cerr << "Loi: Input khong hop le" << endl;
        return 1;
    }

    inputFile.close();

    long long yA = habac(a, xA, q);
    cout << "Khoa cong khai cua An: PU = {" << q << ", " << a << ", " << yA << "}" << endl;
    long long C1 = habac(a, k, q); 
    long long C2 = (M * habac(yA, k, q)) % q; 
    cout << "Ban ma (C1, C2) = (" << C1 << ", " << C2 << ")" << endl;
    long long decrypted_M = (C2 * habac(C1, q - 1 - xA, q)) % q;
    cout << "Giai ma ban ma (C1, C2): " << decrypted_M << endl;

    return 0;
}
