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
        cerr << "Loi: Khong the mo file input" << endl;
        return 1;
    }

    long long q, a, xA, xB;
    if (!(inputFile >> q >> a >> xA >> xB)) {
        cerr << "Loi: Input khong hop le" << endl;
        return 1;
    }

    inputFile.close();

    long long yA = habac(a, xA, q);
    cout << "Khoa cong khai cua Alice: yA = " << yA << endl;

    long long yB = habac(a, xB, q);
    cout << "Khoa cong khai cua Bob: yB = " << yB << endl;

    long long keyA = habac(yB, xA, q);
    long long keyB = habac(yA, xB, q);

    cout << "Khoa chung cua Alice: K = " << keyA << endl;
    cout << "Khoa chung cua Bob: K = " << keyB << endl;

    if (keyA == keyB) {
        cout << "Khoa chung duoc thiet lap thanh cong: K = " << keyA << endl;
    } else {
        cout << "Loi: Khoa chung khong khop!" << endl;
    }

    return 0;
}
