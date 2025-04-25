#include<iostream>
#include<fstream>
using namespace std;
void matran(string key, char a[5][5]){
	bool tick[26]={0};int m=0,n=0;
	for(char c:key){
		if(c>='a'&&c<='z') c-=32;
		if(c=='J') c='I';
		if(c>='A'&&c<='Z'&& !tick[c-'A']){
			a[m][n]=c;
			tick[c-'A']=1;n++;
			if(n==5){
				n=0;m++;
			}
		}
	}
	
	for(char c='A';c<='Z';c++){
		if(c=='J') continue;
		if(!tick[c-'A']){
			a[m][n]=c;n++;
			if(n==5){
				n=0;m++;
			}
		}
	}
}
string input(string txt){
	string in,capkt;
	for(char c:txt){
		if(c>='a'&&c<='z') c-=32;
		if(c=='J') c='I';
		if(c>='A'&&c<='Z') in+=c;
	}
	for(int i=0;i<in.length();i++){
		capkt+=in[i];
		if(i+1<in.length()&&in[i]!=in[i+1]) capkt+=in[++i];
		else capkt+='X';
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

int main(){
	string txt,key;
	ifstream file("input.txt");
	if(!file) return 1;
	getline(file,txt);
	getline(file,key);
	string mahoa=playfair(txt,key);
	cout<<"ma hoa: "<<mahoa<<endl;
	cout<<"giai ma: "<<playfair(mahoa,key,false)<<endl;
}
