#include <iostream>
#include <fstream>
using namespace std;


long long habac(int a, int m, int n) {
    if (m == 0) return 1;
    if (m % 2 == 0) {
        long long half = habac(a, m / 2, n);
        return (half * half) % n;
    }
    return (a * habac(a, m - 1, n)) % n;
}

int tinhLog(int a, int b, int n) {
    for (int x = 0; x < n; x++) 
        if (habac(a, x, n) == b) return x;
    return -1;
}

int main() {
    
    ifstream file("input.txt");
    int a, b, n;
    if(file>>a>>b>>n){
    	int x = tinhLog(a, b, n);
    	if (x != -1) 
        cout << "Logarit roi rac: log_" << a << "(" << b << ") mod " << n << " = " << x << endl;
	}


    return 0;
}
