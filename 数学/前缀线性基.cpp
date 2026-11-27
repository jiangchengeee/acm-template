#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
const int N = 5e5 + 5;
const int LOG = 20;//值域 < 2^LOG，按题目改（改小能省内存）
// 前缀线性基：多次询问 a[l..r] 里选若干个数异或的最大值
// b[i][j]：前 i 个数张成的基里最高位为 j 的基向量
// p[i][j]：上面这个基向量的「来源位置」，插入时优先保留位置更靠右的，这样 p[r][j]>=l 才能用
// 用 int32_t：值域 < 2^20、位置 < 5e5，都装得下，不然被 #define int long long 拖成 8 字节，内存翻倍
int n, q;
static int32_t a[N], b[N][LOG], p[N][LOG];
int query(int l, int r) {
	int res = 0;
	down(j, LOG - 1, 0) {
		if (p[r][j] >= l && (res ^ b[r][j]) > res) res ^= b[r][j];
	}
	return res;
}
void solve() {
	cin >> n;
	up(i, 1, n) cin >> a[i];
	up(i, 1, n) {
		up(j, 0, LOG - 1) b[i][j] = b[i - 1][j], p[i][j] = p[i - 1][j];
		int32_t x = a[i], pos = i;//和 b/p 同类型，不然 swap 推不出模板参数
		down(j, LOG - 1, 0) if ((x >> j) & 1) {
			if (!b[i][j]) { b[i][j] = x, p[i][j] = pos; break; }
			if (pos > p[i][j]) swap(pos, p[i][j]), swap(x, b[i][j]);//位置更靠右的留在基里
			x ^= b[i][j];
		}
	}
	cin >> q;
	while (q--) {
		int l, r;
		cin >> l >> r;
		cout << query(l, r) << '\n';
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
//	cin >> T;
	while (T--) solve();
	return 0;
}
/*
5
2 5 3 6 1
3
1 5
2 4
3 3
// 7
// 6
// 3

要点：
1. 和普通线性基的唯一区别：多存一个 pos，插入时若新元素位置更靠右就交换，保证每个基向量都尽量来自右边；
2. 询问 [l,r] 时只看 p[r][j] >= l 的基向量，等价于「只用 [l,r] 里的数」；
3. 复杂度 O(n log V)，内存 n*LOG（用 int32_t 压一下）；
4. 如果是「选一个子集使异或和与 x 最大」的版本，最后再把答案和 x 异或一遍；
5. 可持久化写法（每个前缀一棵树）比这个多一个 log，一般用不着。
*/
