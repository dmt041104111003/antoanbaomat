#include <fstream>
#include <iostream>

using namespace std;

long long dif(long long co_so, long long so_mu, long long m) {
    long long ket_qua = 1;
    co_so %= m;
    while (so_mu > 0) {
        if (so_mu % 2 == 1)
            ket_qua = (ket_qua * co_so) % m;
        so_mu /= 2;
        co_so = (co_so * co_so) % m;
    }
    return ket_qua;
}

int main() {
    int x = 3 << 3;
	cerr<<x;
    return 0;
}
