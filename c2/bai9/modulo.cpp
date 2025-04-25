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

void tinhbieuthuc(long long a, long long b, long long x, long long y, long long n){
	long long a1,b1;
	if (gcd(a, n) == 1 && gcd(b,n)==1) {
        long long phi_n = euler_phi(n);
        x %= phi_n;
        y %= phi_n;
        a1=habac(a, x, n);b1=habac(b, y, n);
    }
    cout<<"A1 = "<<(a1+b1)%n<<endl;
    long long A2;
    if((habac(a, x, n)-habac(b, y, n))<0) A2=n+(a1-b1)%n;
    A2=(a1-b1)%n;
    cout<<"A2 = "<<A2<<endl;
    cout<<"A3 = "<<(a1*b1)%n<<endl;
    cout<<"A4 = "<<nghichdao(b1,n)<<endl;
    cout<<"A5 = "<<a1*nghichdao(b1,n)%n<<endl;
}
int main() {
    
    ifstream file("input.txt");
	int a, b, x, y, n;
    if (file >> a >> b >> x >> y >> n) tinhbieuthuc(a, b, x, y, n);
        file.close();
    return 0;
}
