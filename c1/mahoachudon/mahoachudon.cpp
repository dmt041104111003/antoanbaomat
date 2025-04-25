#include<iostream>
#include<fstream>
using namespace std;
string chudon(string txt,string key,bool mahoa=true){
	string res="";
	for(int i=0;i<txt.length();i++){
		char c=txt[i];
		if(c>='a'&&c<='z') c-=32;
		if(c>='A'&&c<='Z'){
			if(mahoa) res+=key[c-'A'];
			else{
				for(int j=0;j<key.length();j++)
					if(key[j]==c) res+=char(j+'A');
			}
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
	string mahoa=chudon(txt,key);
	cout<<"ma hoa: "<<mahoa<<endl;
	cout<<"giai ma: "<<chudon(mahoa,key,false)<<endl;
}
