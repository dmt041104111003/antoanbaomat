#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll gcd(ll a, ll b) {
    while (b != 0) {
        ll temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

ll mod_in(ll a, ll m) {
    ll m0 = m, x0 = 0, x1 = 1;
    while (a > 1) {
        ll q = a / m;
        ll temp = m;
        m = a % m;
        a = temp;
        ll temp_x = x1;
        x1 = x0 - q * x1;
        x0 = temp_x;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

int main() {
    ll p = 31, q = 47, e = 43, M = 53, C = 1;
    ll n = p * q;
    ll phi_n = (p - 1) * (q - 1);
    ll d = mod_in(e, phi_n);
    ll base = M % n;
    ll exponent = e;
    while (exponent > 0) {
        if (exponent % 2 == 1) C = (C * base) % n;
        exponent = exponent / 2;
        base = (base * base) % n;
    }
    ll decrypted_M = 1;
    base = C % n; exponent = d;
    while (exponent > 0) {
        if (exponent % 2 == 1) decrypted_M = (decrypted_M * base) % n;
        exponent = exponent / 2;
        base = (base * base) % n;
    }
    cout << "PU = {" << e << ", " << n << "}" << endl << "PR = {" << d << ", " << n << "}" << endl;
	cout << "C = " << C << endl << "M' = " << decrypted_M << endl;
    return 0;
}
