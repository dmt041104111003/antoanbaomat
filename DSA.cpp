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
long long habac(int a, int m, int n) {
    if (m == 0) return 1;
    if (m % 2 == 0) {
        long long half = habac(a, m / 2, n);
        return (half * half) % n;
    }
    return (a * habac(a, m - 1, n)) % n;
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
long long tinhLuyThuaModulo(long long a, long long m, long long n) {
    if (n == 1) return 0;
    a = a % n;
    if (a < 0) a += n;
    if (gcd(a, n) == 1) {
        long long phi_n = euler_phi(n);
        if (phi_n == 0) return habac(a, m, n);
        m = m % phi_n;
        return habac(a, m, n);
    }
    return habac(a, m, n);
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
int main(){
	long long p=47,q=23,h=34,x_A=2,k=10,M_hash=7;
	long long g=tinhLuyThuaModulo(h, (p-1)/q, p);
	long long y_A=tinhLuyThuaModulo(g,x_A,p);
	long long r=tinhLuyThuaModulo(g,k,p)%q;
	long long s=(nghichdao(k,q)*(M_hash+x_A*r)%q);
	long long w=nghichdao(s,q);
	long long u1=(M_hash*w)%q,u2=(r*w)%q;
	long long v = ((tinhLuyThuaModulo(g, u1, p) * tinhLuyThuaModulo(y_A, u2, p)) % p) % q;
	cerr<<"PU cua An y_A: "<<y_A<<endl;
	cerr<<"chu ky so cua An (r,s): "<<r<<","<<s<<endl;
	cerr<<"chu ky so cua An hop le?: "<<((v==r)?"true":"false")<<endl;
}

