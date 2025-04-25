#include <iostream>
#include <fstream>
using namespace std;
string vigenere_lapkhoa(string txt, string key, bool mahoa=true){
	string res="";
	for(int i=0;i<txt.length();i++){
		char c=txt[i],k=key[i%key.length()];
		if(c>='a'&&c<='z') c-=32;
		if(k>='a'&&k<='z') k-=32;
		if(c>='A'&&c<='Z'){
			 if(mahoa)
                res += ((c - 'A' + (k - 'A')) % 26) + 'A';
            else
                res += ((c - 'A' - (k - 'A') + 26) % 26) + 'A';			
		}else res+=c;
	}
	return res;
}
int main(){
	string txt,key;
	ifstream file("input.txt");
	if(!file) return 1;
	getline(file,txt);
	getline(file,key);
	file.close();
	string mahoa=vigenere_lapkhoa(txt,key);
	cout<<"ma hoa: "<<mahoa<<endl;
	cout<<"giai ma: "<<vigenere_lapkhoa(mahoa,key,false);
}
