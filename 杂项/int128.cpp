#include <bits/stdc++.h>
using namespace std;
// 提醒：在 C++ 中，__int128_t 和 __int128 是等价的，一般写 __int128 即可。
inline __int128 read() {
	__int128 x = 0; 
	bool f = 0; 
	char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = 1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return f ? -x : x;
}
inline void print(__int128 x) {
	if (x < 0) { putchar('-'); x = -x; }
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
inline void println(__int128 x) {
	print(x);
	putchar('\n');
}
// 场景：求 (a * b) % mod，其中 a, b, mod 都是 10^18 级别。
// 直接强转 __int128，算完再转回来，绝对不溢出！
long long mul_mod(long long a, long long b, long long mod) {
	// 强制转换为 __int128 后相乘，算完取模，最后再安全地转回 long long
	return (long long)((__int128)a * b % mod);
}
void int128_basics() {
	__int128 a = read();
	__int128 b = read();
	__int128 add = a + b;
	__int128 sub = a - b;
	__int128 mul = a * b;
	__int128 div = a / b;
	__int128 mod = a % b;
	__int128 bit_and = a & b;
	__int128 shift = a << 10;
	print(add); putchar(' '); println(mul);
}
inline __int128 abs_128(__int128 x) {
	return x < 0 ? -x : x;
}
__int128 gcd_128(__int128 a, __int128 b) {
	return b == 0 ? a : gcd_128(b, a % b);
}

void check_limits() {
	// __int128 的最大值大概是 1.7 * 10^38
	__int128 max_val = ((__int128)1 << 126) - 1 + ((__int128)1 << 126);
	cout << "Max __int128 is roughly: ";
	println(max_val); 
	// 输出: 170141183460469231731687303715884105727
}
