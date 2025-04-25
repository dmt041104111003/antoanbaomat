#include <iostream>
#include <fstream>
using namespace std;

long long gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int nghichdao(int a, int m) {
	a=a%m;
	int A1 = 0, A2 = m;
    int B1 = 1, B2 = a;
    int Q, T1, T2;
	while (B2 != 0 && B2 != 1) {
	    Q = A2 / B2;
	    T1 = A1 - Q * B1;
	    T2 = A2 - Q * B2;
	    A1 = B1;
	    B1 = T1;
	    A2 = B2;
	    B2 = T2;
	}
	if (B2 == 0) return -1;
	if (B2 == 1) {
	    if (B1 < 0) return m + B1;
	    return B1;
	}
    return -1;
}


long long habac(int a, int m, int n) {
    if (m == 0) return 1;
    if (m % 2 == 0) {
        long long half = habac(a, m / 2, n);
        return (half * half) % n;
    }
    return (a * habac(a, m - 1, n)) % n;
}

main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Loi: Khong the mo file input" << endl;
        return 1;
    }

    long long p, q, e, M;
    if (!(inputFile >> p >> q >> e >> M)) {
        cerr << "Loi: Input khong hop le" << endl;
        return 1;
    }

    inputFile.close();

    long long n = p * q;
    long long phi_n = (p - 1) * (q - 1);

    long long d = nghichdao(e, phi_n);

    pair<long long, long long> PU = {e, n};
    cout << "Khoa cong khai cua An (PU): {" << PU.first << ", " << PU.second << "}" << std::endl;

    pair<long long, long long> PR = {d, n};
    cout << "Khoa rieng cua An (PR): {" << PR.first << ", " << PR.second << "}" << std::endl;

    long long C = habac(M, e, n);
    cout << "Ba ma hoa cua M = " << M << ": " << C << std::endl;
 
    long long decrypted_M = habac(C, d, n);
    cout << "Giai ma ban ma: " << decrypted_M << std::endl;

    cout << "Viec ma hoa o cau c la thuc hien nhiem vu bao mat." << std::endl;

    return 0;
}

