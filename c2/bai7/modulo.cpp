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

bool cannguyenthuy(int a, int n) {
    if (gcd(a, n) != 1) return false;
    int phi = euler_phi(n);
    if (phi == 0) return false;

    int cacthuasonguyento[1000];
    int count = thuasonguyento(phi, cacthuasonguyento);
    for (int i = 0; i < count; i++) {
        int p = cacthuasonguyento[i];
        if (habac(a, phi / p, n) == 1) return false;
    }

    return true;
}


int main() {
    
    ifstream file("input.txt");
    int a,n;
    if(file>>a>>n){
    	if (cannguyenthuy(a, n)) cout << a << " la can nguyen thuy cua " << n << endl;
	    else cout << a << " khong phai can nguyen thuy cua " << n << endl;
	}
	    

    return 0;
}
