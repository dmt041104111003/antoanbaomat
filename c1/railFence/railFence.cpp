#include <iostream>
#include <fstream>
using namespace std;

string railFence(string text, int key, bool mahoa=true){
    string result = text;
    if (mahoa) {
        int pos = 0;
        for (int i = 0; i < key; i++)
            for (int j = i; j < text.length(); j += key)
                result[pos++] = text[j];
    } else {
        int pos = 0;
        for (int i = 0; i < key; i++)
            for (int j = i; j < text.length(); j += key)
                result[j] = text[pos++];
    }
    return result;				
}

int main(){
	string txt; int key;
    ifstream file("input.txt");
    if (!file) return 1;
    file>>key;file.ignore();
    getline(file, txt);
    file.close();
    string maHoa = railFence(txt, key);
    cout << "ma hoa: " << maHoa << endl<< "giai ma: " << railFence(maHoa, key, false);
}
