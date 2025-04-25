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

int main() {
    
    ifstream file("input.txt");
	int n;
	if(file>>n){
		cout<<euler_phi(n);
	}

    return 0;
}
