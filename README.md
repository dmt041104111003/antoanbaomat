### 1. Mã hóa Caesar
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Mã hóa Caesar là một thuật toán mã hóa cổ điển, dịch chuyển mỗi ký tự trong văn bản theo một số bước nhất định trong bảng chữ cái.

Hàm mã hóa:
```python
string caesar(string tx, int s) {
    string str = "";
    for (char& c : tx) c = toupper(c);
    for (char c : tx) {
        if (isalpha(c)) {
            char ch = ((c - 'A' + s + 26) % 26) + 'A';
            str += ch;
        } else str += c;
    }
    return str;
}
```
Hàm caesar() thực hiện mã hóa bằng cách:

Chuyển tất cả ký tự thành chữ in hoa.

Dịch chuyển ký tự theo giá trị s với phép toán modulo để đảm bảo vòng lặp trong bảng chữ cái.

Giữ nguyên các ký tự không phải chữ cái.

Ví dụ:

Đầu vào: HELLO, khóa 3 → Kết quả: KHOOR

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
### 2. Phép toán Modulo
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Phép toán modulo giúp tính toán phần dư, đảm bảo số không vượt quá phạm vi nhất định.

Hàm tính lũy thừa theo modulo:
```python
ll mod(ll a, ll m, ll n) {
    if (m == 0) return 1;
    else if (m % 2 == 0) {
        ll hp = mod(a, m / 2, n);
        return (hp * hp) % n;
    }
    else return (a * mod(a, m - 1, n)) % n;
}
```
Hàm mod() tính a^m mod n bằng phương pháp chia để trị:

Nếu m = 0, trả về 1.

Nếu m chẵn, tính $a^{\frac{m}{2}}$, sau đó bình phương kết quả.

Nếu m lẻ, nhân thêm a rồi tiếp tục tính đệ quy.

Ví dụ:

$2^{10}$ mod 1000 = 24

<p align="center">_ _ _</p>
