#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
const int N = 5e5 + 5;
// 区间 mex：多次询问 [l,r] 的 mex（P4137）
// 做法：询问按右端点排序；线段树建在「值域 0..n」上，节点维护该值域内每个值最后一次出现位置的最小值
// 扫到 r 时，[l,r] 的 mex 就是最小的 v 满足 last[v] < l
int n, m;
int a[N];
struct code {
	int l, r, id;
	friend bool operator<(code x, code y) { return x.r < y.r; }
} p[N];
struct node {
	int l, r, w;
} t[N << 2];
void pushup(int u) { t[u].w = min(t[u << 1].w, t[u << 1 | 1].w); }
void build(int u, int l, int r) {
	t[u] = {l, r, 0};//初始 last 全 0：还没出现过，等价于出现在位置 0
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}
void update(int u, int pos, int x) {//把值 pos 的最后一次出现位置改成 x
	if (t[u].l == t[u].r) { t[u].w = x; return; }
	int mid = (t[u].l + t[u].r) >> 1;
	if (pos <= mid) update(u << 1, pos, x);
	else update(u << 1 | 1, pos, x);
	pushup(u);
}
int query(int u, int x) {//最小的 v 满足 last[v] < x，即 v 在 [x,r] 里没出现过
	if (t[u].w >= x) return n + 1;//值域 0..n 全都出现过才会走到这里，正常数据不会发生
	if (t[u].l == t[u].r) return t[u].l;
	if (t[u << 1].w < x) return query(u << 1, x);
	return query(u << 1 | 1, x);
}
void solve() {
	cin >> n;
	up(i, 1, n) cin >> a[i];
	cin >> m;
	up(i, 1, m) {
		cin >> p[i].l >> p[i].r;
		p[i].id = i;
	}
	sort(p + 1, p + m + 1);
	vector<int> ans(m + 1, 0);
	build(1, 0, n);
	int pos = 0;
	up(i, 1, m) {
		up(j, pos + 1, p[i].r) if (a[j] >= 0 && a[j] <= n) update(1, a[j], j);//超出值域的值不可能是 mex
		pos = p[i].r;
		ans[p[i].id] = query(1, p[i].l);
	}
	up(i, 1, m) cout << ans[i] << '\n';
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
7
0 1 2 3 4 5 6
5
1 7
2 4
1 1
5 7
2 2
// 7
// 0
// 1
// 0
// 0

要点：
1. 值域取 0..n 共 n+1 个数，而区间里只有不超过 n 个数，所以 mex 必然 <= n；
2. 按右端点排序后每个元素只插入一次，总复杂度 O((n+m)log n)；
3. 把「最后一次出现位置」换成 dfs 序上的位置，就是树上 mex。
*/
