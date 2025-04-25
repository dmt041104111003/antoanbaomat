#include <iostream>
#include <fstream>
using namespace std;
string vigenere_autokey(string txt,string key,bool mahoa=true){
	string res="",fullkey=key;
	for(int i=0;i<txt.length();i++){
		char c=txt[i],k=fullkey[i];
		if(c>='a'&&c<='z') c-=32;
		if(k>='a'&&k<='z') k-=32;
		if(c>='A'&&c<='Z'){
			char new_char;
			if(mahoa){
				new_char=((c-'A'+(k-'A'))%26)+'A';
				fullkey+=c;
			}else{
				new_char=((c-'A'-(k-'A')+26)%26)+'A';
				fullkey+=new_char;
			}
			res+=new_char;
		}else res+=c;
	}
	return res;
}
int main(){
	string txt,key;
	ifstream file("input.txt");
	getline(file,txt);
	getline(file,key);file.close();
	string mahoa=vigenere_autokey(txt,key);
	cerr<<"ma hoa: "<<mahoa<<endl;
	cerr<<"giai ma: "<<vigenere_autokey(mahoa,key,false)<<endl;
}
