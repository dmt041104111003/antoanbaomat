#include <iostream>
#include <fstream>
using namespace std;
string casear(string txt, int k, bool mahoa = true){
	string res = "";
	if (!mahoa) k = -k;
	for (char c : txt){
		if (c >= 'a' && c <= 'z') c -= 32;
		if (c >= 'A' && c <= 'Z') res += ((c - 'A' + k + 26)%26) + 'A';
		else res += c;
	}
	return res;
}

string vigenere_lapkhoa(string txt, string key, bool mahoa = true){
	string res = "";
	for (int i = 0; i <txt.length();i++){
		char c = txt[i], k = key[i%key.length()];
		if (c >= 'a' && c <= 'z') c -= 32;
		if (k >= 'a' && k <= 'z') k -= 32;
		if (c >= 'A' && c <= 'Z'){
			if (!mahoa) k = -k;
				res += ((c - 'A' - (k-'A') + 26)%26) + 'A';
		} else res += c;
	}
	return res;
}

string vigenere_autokey(string txt, string key, bool mahoa = true) {
    string res = "", fullkey=key;
    for (int i = 0; i<txt.length();i++){
    	char c = txt[i], k = fullkey[i];
    	if (c >= 'a' && c <= 'z') c -= 32;
		if (k >= 'a' && k <= 'z') k -= 32;
		if (c >= 'A' && c <= 'Z'){
			char new_char;
            if (mahoa) {
                new_char = ((c - 'A' + (k - 'A')) % 26) + 'A';
                fullkey += c;
            } else {
                new_char = ((c - 'A' - (k - 'A') + 26) % 26) + 'A';
                fullkey += new_char;
            }
            res += new_char;
		} else res += c;
	}
	return res;
}
string monocipher(string txt, string key, bool mahoa = true){
	string res = "";
	for (int i=0; i<txt.length();i++){
		char c = txt[i];
		if (c >= 'a' && c <= 'z') c -= 32;
		if (c >= 'A' && c <= 'Z'){
            if (mahoa) res += key[c-'A'];
            else {
                for (int j=0;j<key.length();j++)
	                if (key[j] == c) res += char(j + 'A');
            }
		} else res += c;
	}
	return res;
}
// playfair
void matran(string key, char a[5][5]){
	bool tick[26]={0}; int m=0,n=0;
	for (char c:key){
        if (c >= 'a' && c <= 'z') c -= 32;
        if(c == 'J') c = 'I';
        if(c>= 'A' && c<='Z' && !tick[c - 'A']){
        	a[m][n]=c;
        	tick[c-'A']=1; n++;
        	if(n==5){
        		n=0; m++;
			}
		}
	}
	
	for (char c='A'; c<='Z';c++){
		if(c=='J') continue;
		if(!tick[c-'A']){
			a[m][n]=c; n++;
			if(n==5){
				n=0;m++;
			}
		}
	}
}
string input(string txt){
	string in, capkt;
	for(char c:txt){
		if (c >= 'a' && c <= 'z') c -= 32;
        if (c == 'J') c = 'I';
        if (c >= 'A' && c <= 'Z') in += c;
	}
	for(int i=0;i<in.length();i++){
		capkt += in[i];
		if(i+1<in.length()&&in[i]!=in[i+1]) capkt += in[++i];
		else capkt +='X';
	}
	return capkt;
}

string playfair(string txt, string key, bool mahoa = true){
	char a[5][5]={0}; matran(key, a);
	string capkt = input(txt), res;
	for(int i=0;i<capkt.length();i+=2){
		char x=capkt[i], y=capkt[i+1];
		int m1,m2,n1,n2;
		
		for(int m=0;m<5;m++){
			for(int n=0;n<5;n++){
				if(a[m][n]==x){
					m1=m;n1=n;
				}
				if(a[m][n]==y){
					m2=m;n2=n;
				}
			}
		}
		
		if(m1==m2){
			int k = mahoa?1:-1;
			res +=a[m1][(n1+k+5)%5];
			res +=a[m2][(n2+k+5)%5];
		}else if( n1==n2){
			int k = mahoa?1:-1;
			res +=a[(m1+k+5)%5][n1];
			res +=a[(m2+k+5)%5][n2];
		}else{
			res +=a[m1][n2];
			res +=a[m2][n1];
		}
	}
	return res;
}

//bai 6 hoan vi
//1 cho k=1 so
string railFence(string text, string keyText, bool mahoa=true){
	int key = 0;
    for (char c : keyText)
        if (c >= '0' && c <= '9') key = key * 10 + (c - '0');
    string result = text;
    if (mahoa) {
        int pos = 0;
        for (int i = 0; i < key; i++)
            for (int j = i; j < text.size(); j += key)
                result[pos++] = text[j];
    } else {
        int pos = 0;
        for (int i = 0; i < key; i++)
            for (int j = i; j < text.size(); j += key)
                result[j] = text[pos++];
    }
    return result;				
}
//2 cho k=12143
void matran(char a[100][100], string banro, int m, int n) {
    int index = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = (index < banro.length()) ? banro[index++] : 0;
}

string hoanvi(string banro, string key, bool mahoa = true, int padding = 0) {
    int n = key.length();
    int m = banro.length() / n;
    char a[100][100] = {};
    int pos[100] = {};
    bool tick[100] = {};

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!tick[j] && key[j] == '1' + i) {
                pos[i] = j;
                tick[j] = true;
            }

    if (mahoa) {
        matran(a, banro, m, n);
        string banma;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (a[j][pos[i]])
                    banma += a[j][pos[i]];
        return banma;
    } else {
        string giaima;
        int index = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m && index < banro.length(); j++)
                a[j][pos[i]] = banro[index++];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (a[i][j])
                    giaima += a[i][j];
        if (padding > 0) {
		    string temp = "";
		    for (int i = 0; i < giaima.length() - padding; i++)
		        temp += giaima[i];
		    giaima = temp;
		}
        return giaima;
    }
}

int main() {
    ifstream file("input_HoanVi2.txt");
    string key, banRo;
    getline(file, key);
    getline(file, banRo);
    file.close();
    int n = key.length();
    int padding = 0;
    while ((banRo.length() % n)!=0) {
        banRo += 'Z' - (n - banRo.length() % n) + 1;
        padding++;
    }
    string banMa = hoanvi(banRo, key, true); 
    string banGiaiMa = hoanvi(banMa, key, false, padding);
    cout << "Ban ma: " << banMa << endl;
    cout << "Ban giai ma: " << banGiaiMa << endl;

    return 0;
}
int main (){
	string txt; int k;
	ifstream file ("input.txt");
	if (!file) return 1;
	getline(file,txt);
	file >> k; file.close();
	string mahoa=casear(txt,k);
	cout<< "ma hoa: "<< mahoa <<"\n"<<"giai ma: "<<casear(mahoa,k,false);
}
//    ifstream file("input_HoanVi2.txt");
//    string khoa, banRo;
//    getline(file, khoa);
//    getline(file, banRo);
//    file.close();
//    int soCot = khoa.length();
//    while (banRo.length() % soCot)
//        banRo += 'Z' - (soCot - banRo.length() % soCot) + 1;
//    cout << hoanvi(banRo, khoa) << endl; 

//    string key, txt;
//    ifstream file("input_HoanVi.txt");
//    if (!file) return 1;
//    getline(file, key);
//    getline(file, txt);
//    file.close();
//    string maHoa = railFence(txt, key);
//    cout << "ma hoa: " << maHoa << endl<< "giai ma: " << railFence(maHoa, key, false);
//    return 0;
