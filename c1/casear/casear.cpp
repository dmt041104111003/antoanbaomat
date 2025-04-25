#include<iostream>
#include<fstream>
using namespace std;
string casear(string txt, int k, bool mahoa=true){
	string res="";
	if(!mahoa) k=-k;
	for(char c:txt){
		if(c>='a'&&c<='z') c-=32;
		if(c>='A'&&c<='Z')
			if(mahoa) res+=((c-'A'+k)%26)+'A';
			else res+=((c-'A'+k+26)%26)+'A';
		else res+=c;
	}
	return res;
}
int main(){
	string txt; int k;
	ifstream file("input.txt");
	if(!file) return 1;
	getline(file,txt);
	file>>k;file.close();
	string mahoa=casear(txt,k);
	cout<<"ma hoa: "<<mahoa<<"\n";
	cout<<"giai ma: "<<casear(mahoa,k,false);
}
