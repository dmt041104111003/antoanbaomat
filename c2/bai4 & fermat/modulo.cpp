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
        long long k = m / phi_n;
        long long r = m % phi_n;
        long long result = habac(a, r, n);
        if (k > 0) {
            long long euler = habac(a, phi_n, n);
            euler = habac(euler, k, n);
            result = (result * euler) % n;
        }
        return result;
    }
    return habac(a, m, n);
}
long long tinhLuyThuaModuloFerma(long long a, long long m, long long n) {
    if (n == 1) return 0;
    a = a % n;
    if (a < 0) a += n;

    if (laSoNguyenTo(n) && gcd(a, n) == 1) {
        long long p_minus_1 = n - 1;
        long long k = m / p_minus_1;
        long long r = m % p_minus_1;
        long long result = habac(a, r, n);
        if (k > 0) {
            long long ferma = habac(a, p_minus_1, n);
            ferma = habac(ferma, k, n);
            result = (result * ferma) % n;
        }
        return result;
    }
    return habac(a, m, n);
}

int main() {
    
    ifstream file("input.txt");
	int a,m,n;
	if(file>>a>>m>>n) cout<<"kq "<< a<<"^" <<m<<" mod "<<n<<" la: "<<tinhLuyThuaModuloFerma(a,m,n)<<endl;
	file.close();

    return 0;
}
