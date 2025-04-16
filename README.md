# I. Ma hoa co dien
## 1. Caesar

Hàm `caesar`:
```cpp
string caesar(string text, int k, bool encode = true) {
    string result = "";
    if (!encode) k = -k; // Nếu không phải mã hóa thì đảo chiều của k
    for (char c : text) {
        if (c >= 'A' && c <= 'Z')
            c = ((c - 'A' + k + 26) % 26) + 'A';
        else if (c >= 'a' && c <= 'z') 
            c = ((c - 'a' + k + 26) % 26) + 'a';
        result += c;
    }
    return result;
}
```
a. input:
text = SAVEFORARAINYDAY
k = 25  
b. step ma hoa (encode = true):  
text = S -> qua ` c = ((83 - 65+ 25 + 26) % 26) + 65; ` -> c = 82 (ASCII) -> R  
. . . tuong tu cho den khi ma hoa thanh cong  
-> output ma hoa = RZUDENQZQZHMXCZX  
c. step giai ma (encode = false):  
k = -k = -25
text = R -> qua `c = ((82 - 65 - 25 + 26) % 26) + 65;` -> c = 83 (ASCII) -> S  
-> output giai ma = SAVEFORARAINYDAY  

## 2. Vigenere  
### Lap khoa
```cpp
string vigenere(string text, string key, bool encode = true) {
    string result = "";
    string key_upper = key; // tao 1 ban sao key
    for (char& c : key_upper) 
        if (c >= 'a' && c <= 'z') c = c - ('a' - 'A'); // chuyen thuong -> hoa
    int key_len = key_upper.length();
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            char base = (c >= 'a') ? 'a' : 'A';
            if (base == 'a') c = c - ('a' - 'A');
            char k = key_upper[i % key_len]; // lap lai ky tu khoa, vd: text = WHENINROMEDO la 12 ky tu, key = THETRU la 6 -> key_upper = THETRUTHETRU
            if (encode)
                c = ((c - 'A' + (k - 'A') + 26) % 26) + 'A'; // tuong tu Caesar encode = true la ma hoa
            else // encode = false thi giai ma
                c = ((c - k + 26) % 26) + 'A';
        }
        result += c; // add ky tu c vao cuoi chuoi
    }
    return result;
}
```
a. input:
text = WHENINROMEDO
key = THETRU  
b. step ma hoa: (mo ta trong code)  
c. step giai ma: (mo ta trong code)  

### Auto-key
```cpp
string vigenere(string text, string key, bool encode) {
    string result = "";
    string full_key = key; // tra tung kytu key tuong ung, ban dau la LIKEFA
    for (int i = 0; i < text.length(); i++) {
        char c = (text[i] >= 'a' && text[i] <= 'z') ? text[i] - 32 : text[i]; // thuong -> hoa
        if (c >= 'A' && c <= 'Z') {
            char k = (i < full_key.length()) ? full_key[i] : result[i - key.length()]; // trong pham vi ban dau -> lay key[i], neu ngoai thi sinh them
                                                                                        // vd: i = 0 -> LIKEFA[i], i = 6 -> result[6-6] = [0] = text0 = B
            k = (k >= 'a' && k <= 'z') ? k - 32 : k; 
            int shift = encode ? (k - 'A') : -(k - 'A');  // encode = true ma hoa, false thi giai ma vd key vi tri L, L - A = 76 - 65 = 11 -> 11 (ma hoa) & -11(giai ma)
            result += (c - 'A' + shift + 26) % 26 + 'A'; // vd: c = B tuong ung key = L -> shift = 11 (key = L) -> result = 66 - 65 + 11 + 26) % 26 + 65 = 77 (M) ma hoa
            if (encode) full_key += c; // LIKEFA -> LIKEFABAKKIN = 12 ky tu = BAKKINGDOGSS
        } else result += c; // tra ve nguyen vao chuoi
    }
    return result;
}
```
a. input:
text = BARKINGDOGSS  
key = LIKEFA  
b. step ma hoa: (mo ta trong code)  
c. step giai ma: (mo ta trong code)  
## 3. Ma hoa chu don

```cpp
string monoCipher(string text, string key, bool encode) {
    string result = "";
    string k = key;
    for (char& c : k) if (c >= 'a' && c <= 'z') c -= 32;
    for (char c : text) {
        char ch = (c >= 'a' && c <= 'z') ? c - 32 : c;
        if (ch >= 'A' && ch <= 'Z') {
            if (encode) result += k[ch - 'A']; // vd P - A = 80 - 65 = 15 -> key[15] = Z
            else {
                for (int i = 0; i < k.length(); i++) {
                    if (k[i] == ch) { // vd key[i] = Z -> i = 15
                        result += char(i + 'A'); // 15 + 65 = 80 0-> P
                        ch = 0; 
                        break;
                    }
                }
                if (ch != 0) result += '?';
            }
        } else result += ch;
    }
    return result;
}
```
a. input:  
text = PENNYWISEPOUNDFO  
key = KGOXPMUHCAYTJQWZRIVESFLDNB  
b. step ma hoa: (mo ta trong code)  
c. step giai ma: (mo ta trong code)  
## 4. PLayfair

```cpp
string playfair(string text, string key) {
    char table[5][5] = {0}; // tao bang 5x5 chua ma hoa
    bool used[26] = {0}; // danh dau chu cai da dung
    int row = 0, col = 0;

    for (char c : key) {// thuong -> hoa
        c = toupper(c);
        if (c == 'J') c = 'I'; // j va i la 1
        if (c >= 'A' && c <= 'Z' && !used[c - 'A']) {
            table[row][col] = c;
            used[c - 'A'] = 1; // add + danh dau da dung
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    for (char c = 'A'; c <= 'Z'; c++) { // muc tieu dien not vao bang
        if (c == 'J') continue; // bo qua j neu chua dung
        if (!used[c - 'A']) { // chua dung thi gan vao bang
            table[row][col] = c;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }


| Ký tự trong `text` | Chuyển sang chữ hoa | Thay J → I | Là chữ A–Z? | Thêm vào `prepared` |
|--------------------|---------------------|------------|-------------|---------------------|
| S                  | S                   | —          | v          | → S                  |
| O                  | O                   | —          | v          | → SO                 |
| F                  | F                   | —          | v          | → SOF                |
| A                  | A                   | —          | v          | → SOFA               |
| R                  | R                   | —          | v          | → SOFAR              |
| S                  | S                   | —          | v          | → SOFARS             |
| O                  | O                   | —          | v          | → SOFARSO            |
| G                  | G                   | —          | v          | → SOFARSOG           |
// tuong tu ...
    string prepared;
    for (char c : text) {
        c = toupper(c);
        if (c == 'J') c = 'I';
        if (c >= 'A' && c <= 'Z') prepared += c;
    }


// vd: prepared = S O F A R S O G O O D S O
// i = 0 prepared[0] = S, prepared[1] = O → khác nhau ⇒ thêm SO vào pairs, i tăng thêm 1 → i = 2
// tuong tu ... prepared[8] = O, prepared[9] = O → giống nhau ⇒ không lấy ký tự tiếp theo, mà: thêm X vào ⇒ cặp là OX, i không tăng
// pairs = SOFA RSOG OXOD SO


    string pairs;
    for (int i = 0; i < prepared.size(); i++) {
        pairs += prepared[i];
        if (i + 1 < prepared.size() && prepared[i] != prepared[i + 1]) {
            pairs += prepared[++i];
        } else {
            pairs += 'X';
        }
    }

    string cipher;
    for (int i = 0; i < pairs.size(); i += 2) {
        char a = pairs[i], b = pairs[i + 1];
        int r1, c1, r2, c2;

        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                if (table[r][c] == a) {
                    r1 = r; c1 = c;
                }
                if (table[r][c] == b) {
                    r2 = r; c2 = c;
                }
            }
        }

        if (r1 == r2) {
            cipher += table[r1][(c1 + 1) % 5];
            cipher += table[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            cipher += table[(r1 + 1) % 5][c1];
            cipher += table[(r2 + 1) % 5][c2];
        } else {
            cipher += table[r1][c2];
            cipher += table[r2][c1];
        }
    }
| Cặp  | Vị trí `a` | Vị trí `b` | Trường hợp   | Mã hóa thành |
|------|------------|------------|---------------|---------------|
| S O  | (0,2)      | (0,4)      | Cùng hàng     | T, E          |
| F A  | (2,0)      | (0,1)      | Khác          | G, S          |
| R S  | (1,0)      | (0,2)      | Khác          | B, E          |
| O G  | (0,4)      | (2,1)      | Khác          | A, K          |
| O X  | (0,4)      | (4,2)      | Khác          | S, Z          |
| O D  | (0,4)      | (1,4)      | Cùng cột      | D, K          |
| S O  | (0,2)      | (0,4)      | Cùng hàng     | T, E          |

    return cipher;
}
```
a. input:  
text = SOFARSOGOODSO  
key = EASTORW  
b. step ma hoa: (mo ta trong code)  
c. step giai ma: (mo ta trong code)  
