#include <iostream>
#include <fstream>

using namespace std;

long long modular_pow(long long base, long long exponent, long long modulus) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent = exponent / 2;
    }
    return result;
}

main() {
    ifstream inputFile("inputElgamal.txt");
    if (!inputFile.is_open()) {
        cerr << "Loi: Khong the mo file input" << endl;
        return 1;
    }

    long long q, a, xA, k, M;
    if (!(inputFile >> q >> a >> xA >> k >> M)) {
        cerr << "Loi: Input khong hop le" << endl;
        return 1;
    }

    inputFile.close();

    long long yA = modular_pow(a, xA, q);

    cout << "Khoa cong khai cua An: PU = {" << q << ", " << a << ", " << yA << "}" << endl;

    long long C1 = modular_pow(a, k, q);
    long long C2 = (M * modular_pow(yA, k, q)) % q;

    cout << "Ban ma (C1, C2) = (" << C1 << ", " << C2 << ")" << endl;

    long long decrypted_M = (C2 * modular_pow(C1, q - 1 - xA, q)) % q;
    cout << "Giai ma ban ma (C1, C2): " << decrypted_M << endl;

    return 0;
}

