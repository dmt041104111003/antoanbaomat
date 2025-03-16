### 1. Mã hóa Caesar
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Mã hóa Caesar là một thuật toán mã hóa cổ điển, dịch chuyển mỗi ký tự trong văn bản theo một số bước nhất định trong bảng chữ cái.
> Là phương pháp mã hóa đơn giản nhất
> Là cơ sở để phát triển các thuật toán mã hóa đối xứng ngày nay
–> Mọi mã cổ điển là mã đối xứng

**Hàm mã hóa**:
```cpp
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
> Giả sử $\ n \in \mathbb{N}^{+} \$, $\ a \in \mathbb{Z} \$, nếu:
> trong đó r là phần dư dương 0 ≤ r < n và q là thương nguyên lớn nhất ≤ $\frac{a}{n}$.<br>
Khi đó, ký hiệu phần dư dương $r = a \mod n$ và $\ q = \left\lfloor \frac{a}{n} \right\rfloor \$, vậy:<br>
> $$\displaystyle a = \left\lfloor \frac{a}{n} \right\rfloor \cdot n + a \mod n$$
> Ví dụ:     
> $11 \mod 7 = 4$,    vì   11 = 1.7 + 4

**Hàm tính lũy thừa theo modulo**:
```cpp
ll mod(ll a, ll m, ll n) {
    if (m == 0) return 1;
    else if (m % 2 == 0) {
        ll hp = mod(a, m / 2, n);
        return (hp * hp) % n;
    }
    else return (a * mod(a, m - 1, n)) % n;
}
```
Hàm mod() tính $a^m$ mod n bằng phương pháp chia để trị:
Nếu m = 0, trả về 1.
Nếu m chẵn, tính $a^{\frac{m}{2}}$, sau đó bình phương kết quả.
Nếu m lẻ, nhân thêm a rồi tiếp tục tính đệ quy.

Ví dụ:
$2^{10}$ mod 1000 = 24

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
### 3. RSA
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Được sáng tạo bởi `Rivest, Shamir & Adleman` tại MIT vào năm `1977`. Là `mã công khai` được biết đến và sử dụng rộng rãi nhất. Dựa trên `lũy thừa trong trường hữu hạn` với số nguyên `modulo nguyên tố` Là `mã khối` trong đó:  
  - Mỗi khối là một số nguyên thuộc đoạn `[0; n - 1]`.  
  - $$n \leq 2^{1024}$$ → Kích thước khối $\ \leq \log_2(n) + 1 \$.  
Hiện tại, được xem là `mã công khai an toàn nhất`.

**Nguyên lý thuật toán mã hóa RSA**
> M: plaintext block<br>C: ciphertext block.<br>Khi đó:
  *C = Mᵉ mod n*  
  *M = Cᵈ mod n = (Mᵉ)ᵈ mod n = Mᵉᵈ mod n*  
⇒ **Khóa công khai PU = {e, n}**  
⇒ **Khóa riêng PR = {d, n}**

**Khởi tạo khóa RSA**

| **1. Sinh khóa (Alice)** | **Ví dụ** |
|--------------------------|----------|
| Chọn p, q là hai số nguyên tố khác nhau | p = 17 & q = 11 |
| Tính n = pq | n = 17 × 11 = 187 |
| Tính ϕ(n) = (p - 1)(q - 1) | ϕ(n) = 16 × 10 = 160 |
| Chọn số nguyên e, gcd(ϕ(n), e) = 1; 1 < e < ϕ(n) | Chọn e = 7, thỏa mãn gcd(7,160) = 1 |
| Tính d ≡ e⁻¹ (mod ϕ(n)) | d = 23 vì 23 × 7 ≡ 1 (mod 160) |
| **Khóa công khai:** PU = {e, n} | PU = {7, 187} |
| **Khóa riêng:** PR = {d, n} | PR = {23, 187} |

**Mã hóa và Giải mã với RSA**

| |**2. Bob mã hóa với khóa công khai của Alice** | **Ví dụ** |
|-|-------------------------------------|----------|
| **Bản rõ** | M < n | **M = 88** |
| **Bản mã** | C = Mᵉ mod n | C = 88⁷ mod 187 = 11 |


| |**3. Alice giải mã bằng khóa riêng của Alice** | **Ví dụ** |
|-|-----------------------------------|----------|
| **Bản mã** | C | **C = 11** |
| **Bản rõ** | M = Cᵈ mod n | M = 11²³ mod 187 = 88 |

**RSA:**
```cpp
// Mã hóa: C = M^e mod n
ll C = 1, base = M % n, exponent = e;
while (exponent > 0) {
    if (exponent % 2 == 1) C = (C * base) % n;
    exponent /= 2;
    base = (base * base) % n;
}
```
```cpp
// Giải mã: M' = C^d mod n
ll decrypted_M = 1;
base = C % n; exponent = d;
while (exponent > 0) {
    if (exponent % 2 == 1) decrypted_M = (decrypted_M * base) % n;
    exponent /= 2;
    base = (base * base) % n;
}
```

<p align="center">_ _ _</p>
