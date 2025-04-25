#include <iostream>
#include <fstream>
using namespace std;
bool laSoNguyenTo(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) if (n % i == 0) return false;
    return true;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int thuasonguyento(long long M, int mi[]) {
    int k = 0;
    for (int i = 2; i * i <= M; i++) {
        if (M % i == 0 && laSoNguyenTo(i)) {
            mi[k++] = i;
            while (M % i == 0) M /= i;
        }
    }
    if (M > 1) mi[k++] = M;
    return k;
}

long long habac(int a, int m, int n) {
    if (m == 0) return 1;
    if (m % 2 == 0) {
        long long half = habac(a, m / 2, n);
        return (half * half) % n;
    }
    return (a * habac(a, m - 1, n)) % n;
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
int euler_phi(int n) {
    if (laSoNguyenTo(n)) return n - 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int j = n / i, p = i, t = 0, temp = n;
            while (temp % p == 0) {
                temp /= p;
                t++;
            }
            if (temp == 1) {
                int pt = 1, pt_minus_1 = 1;
                for (int k = 0; k < t; k++) pt *= p;
                for (int k = 0; k < t - 1; k++) pt_minus_1 *= p;
                return pt - pt_minus_1;
            }
            if (laSoNguyenTo(i) && laSoNguyenTo(j)) return (i - 1) * (j - 1);
            if (gcd(i, j) == 1) return euler_phi(i) * euler_phi(j);
        }
    }

    return 0;
}

long long tinhCRT(long long a, long long m, long long M) {
    int mi[1000];
    int k = thuasonguyento(M, mi);
    long long A = 0;
    for (int i = 0; i < k; i++) {
        long long phi_mi = euler_phi(mi[i]), reduced_m = m;
        if (gcd(a, mi[i]) == 1) reduced_m = m % phi_mi;
        long long ai = habac(a, reduced_m, mi[i]), Mi = M / mi[i];
        long long Mi_inv = nghichdao(Mi, mi[i]);
        long long ci = (Mi * Mi_inv) % M;
        A = (A + ai * ci) % M;
    }
    return A;
}
long long giaiHeCRT(int m1, int m2, int m3, int a1, int a2, int a3) {
    if (gcd(m1, m2) != 1 || gcd(m2, m3) != 1 || gcd(m1, m3) != 1) {
        cout << "Cac modulo phai doi mot nguyen to cung nhau!" << endl;
        return -1;
    }
    long long M = (long long)m1 * m2 * m3;
    long long M1 = M / m1;
    long long M2 = M / m2;
    long long M3 = M / m3;
    long long M1_inv = nghichdao(M1, m1);
    long long M2_inv = nghichdao(M2, m2);
    long long M3_inv = nghichdao(M3, m3);
    if (M1_inv == -1 || M2_inv == -1 || M3_inv == -1) return -1;
    long long term1 = tinhCRT(a1, 1, M) * (M1 % M) * (M1_inv % M) % M;
    long long term2 = tinhCRT(a2, 1, M) * (M2 % M) * (M2_inv % M) % M;
    long long term3 = tinhCRT(a3, 1, M) * (M3 % M) * (M3_inv % M) % M;
    long long x = (term1 + term2 + term3) % M;
    if (x < 0) x += M;
    return x;
}


int main() {
    
    ifstream file("input.txt");
    int m1, m2, m3, a1, a2, a3;
    if (file >> m1 >> m2 >> m3 >> a1 >> a2 >> a3) {
    	long long x = giaiHeCRT(m1, m2, m3, a1, a2, a3);
        if (x != -1) 
            cout << "x = " << x ;
	}

    return 0;
}
