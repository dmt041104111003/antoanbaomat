#include <iostream>
#include <fstream>
using namespace std;

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

int main() {
    
    ifstream file("input.txt");
    int a,m;
    if (file >> a >> m) {
        int nghichdao1 = nghichdao(a, m);
        if (nghichdao1 != -1)
            cout << "Nghich dao modulo " << a << " mod " << m << " la: " << nghichdao1 << endl;
        else cout<<"khong co nghich dao";
        file.close();
    } else return 1;

    return 0;
}
