#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
// 三分：求单峰函数的最值。凸函数（中间低两边高）用 *_min，凹函数（中间高两边低）用 *_max
// 函数用 lambda 传进来，所以实数、整数、二维（三分套三分）都能直接用
//   例：auto f = [&](long double x){ return (x - 2) * (x - 2) + 3; };
//       long double x = ternary_min(-10, 10, f);   // 极小值点

// ---------- 实数域 ----------
// 在 [l, r] 上找极小值点，返回 x（要函数值就再求一次 f(x)）
template <class F>
double ternary_min(double l, double r, F f)
{
	up(it, 1, 100) {//100 次收缩后区间缩小到 (2/3)^100，早就到 double 精度极限
		double m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
		if (f(m1) < f(m2)) r = m2;//极小值在 [l, m2] 里
		else l = m1;              //极小值在 [m1, r] 里
	}
	return (l + r) / 2;
}
// 找极大值点：对 -f 求极小
template <class F>
double ternary_max(double l, double r, F f)
{
	return ternary_min(l, r, [&](double x) { return -f(x); });
}

// ---------- 整数域 ----------
// 先收缩到长度 <= 2，再暴力比较剩下的几个点（整数下这样最稳，不会因为取整漏掉答案）
template <class F>
int ternary_min_int(int l, int r, F f)
{
	while (r - l > 2) {
		int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
		if (f(m1) < f(m2)) r = m2;
		else l = m1;
	}
	int best = l;
	up(i, l + 1, r)if (f(i) < f(best))best = i;
	return best;
}
// 极大值点：同样对 -f 求极小
template <class F>
int ternary_max_int(int l, int r, F f)
{
	return ternary_min_int(l, r, [&](int x) { return -f(x); });
}

void solve(){
	auto f = [](double x) { return (x - 2) * (x - 2) + 3; };//凸：最小值在 x=2
	auto g = [](double x) { return -(x + 1) * (x + 1) + 5; };//凹：最大值在 x=-1
	auto h = [](int x) { return (x - 5) * (x - 5); };//凸：最小值在 x=5
	auto t = [](int x) { return -(x - 7) * (x - 7) + 9; };//凹：最大值在 x=7

	double x1 = ternary_min(-10.0, 10.0, f);
	double x2 = ternary_max(-10.0, 10.0, g);
	int x3 = ternary_min_int(0, 20, h);
	int x4 = ternary_max_int(0, 20, t);

	cout << fixed << setprecision(6);
	cout << "凸(实) 极值点 x = " << x1 << "，值 = " << f(x1) << '\n';
	cout << "凹(实) 极值点 x = " << x2 << "，值 = " << g(x2) << '\n';
	cout << "凸(整) 极值点 x = " << x3 << "，值 = " << h(x3) << '\n';
	cout << "凹(整) 极值点 x = " << x4 << "，值 = " << t(x4) << '\n';
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int t = 1;
//	cin >> t;
	while (t--){
		solve();
	}
	return 0;
}
/*
凸(实) 极值点 x = 2.000000，值 = 3.000000
凹(实) 极值点 x = -1.000000，值 = 5.000000
凸(整) 极值点 x = 5，值 = 0
凹(整) 极值点 x = 7，值 = 9

拓展：
1. 二维（三分套三分）：外层三分 y，内层对每个 y 三分 x 求最优，注意外层函数值就是内层的最优值；
2. 复杂度：实数域 O(100) 次求值，整数域 O(log n) 次求值；
3. 函数必须严格单峰（或有平顶也行），多峰的题要换思路。
*/
