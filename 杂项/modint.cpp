#include <bits/stdc++.h>
using namespace std;

// ==========================================
// 1. 取模类
// ==========================================
// MOD 作为模板参数，便于编译期常数优化。
template <int MOD>
struct ModInt {
	int val;
	
	// 构造函数：把值归一到 [0, MOD) 并防溢出
	ModInt(long long v = 0) {
		if (v < 0) v = v % MOD + MOD;
		if (v >= MOD) v %= MOD;
		val = v;
	}
	
	// 四则运算，结果均已取模
	ModInt& operator+=(const ModInt& rhs) {
		val += rhs.val;
		if (val >= MOD) val -= MOD; // 用减法代替取模
		return *this;
	}
	ModInt& operator-=(const ModInt& rhs) {
		val -= rhs.val;
		if (val < 0) val += MOD;
		return *this;
	}
	ModInt& operator*=(const ModInt& rhs) {
		val = 1ll * val * rhs.val % MOD;
		return *this;
	}
	ModInt& operator/=(const ModInt& rhs) {
		// 除法转为乘逆元，要求 MOD 为素数
		return *this *= rhs.inv();
	}
	
	// 四则运算符
	friend ModInt operator+(ModInt lhs, const ModInt& rhs) { return lhs += rhs; }
	friend ModInt operator-(ModInt lhs, const ModInt& rhs) { return lhs -= rhs; }
	friend ModInt operator*(ModInt lhs, const ModInt& rhs) { return lhs *= rhs; }
	friend ModInt operator/(ModInt lhs, const ModInt& rhs) { return lhs /= rhs; }
	
	// 一元运算符：取负、自增、自减
	ModInt operator-() const { return ModInt(-val); }
	ModInt& operator++() { return *this += 1; }
	ModInt operator++(int) { ModInt tmp = *this; ++*this; return tmp; }
	ModInt& operator--() { return *this -= 1; }
	ModInt operator--(int) { ModInt tmp = *this; --*this; return tmp; }
	
	// 比较运算符
	bool operator==(const ModInt& rhs) const { return val == rhs.val; }
	bool operator!=(const ModInt& rhs) const { return val != rhs.val; }
	
	// 快速幂，O(log k)
	ModInt pow(long long k) const {
		ModInt res = 1, a = *this;
		while (k > 0) {
			if (k & 1) res *= a;
			a *= a;
			k >>= 1;
		}
		return res;
	}
	
	// 求逆元：费马小定理，要求 MOD 为素数
	ModInt inv() const {
		// a^(p-2) 即 a 的逆元 (mod p)
		return pow(MOD - 2);
	}
	
	// 输入输出重载
	friend istream& operator>>(istream& is, ModInt& m) {
		long long v; is >> v; m = ModInt(v); return is;
	}
	friend ostream& operator<<(ostream& os, const ModInt& m) {
		return os << m.val;
	}
};

// ==========================================
// 2. 使用示例
// ==========================================
// 998244353 与 1e9+7 是常用模数
using mint = ModInt<998244353>;
// using mint = ModInt<1000000007>;

void modint_example() {
	// 1. 读入
	mint a, b;
	// 假设输入 998244354 2
	// cin >> a >> b; 
	a = 998244354; // 自动归约为 1
	b = 2;
	
	// 2. 各运算符结果均已取模
	mint sum = a + b;       // 1 + 2 = 3
	mint sub = a - b;       // 1 - 2 = -1，自动转为 998244352
	mint mul = a * b * 10;  // 连乘不溢出
	
	// 3. 除法自动求逆元
	mint div = a / b;       // 等价于 1 * inv(2)
	
	// 4. 快速幂
	mint ans = a.pow(10086); 
	
	// cout << sum << " " << div << endl;
}
