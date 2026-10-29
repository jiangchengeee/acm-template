#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
mt19937_64 gen(12345);
const int N=1e6+5,inf=0x3f3f3f3f3f3f3f3f;;
int n,m,q,k,mod=998244353;
int a[N],b[N],c[N],d[N];

// 整除分块：n/i 只有 O(√n) 种取值，把取值相同的 i 合成一段处理
//   floor 版：v = n/l，这一段右端点 r = n/v
//   ceil  版：ceil(n/i) = floor((n-1)/i) + 1，所以对 n-1 做 floor 分块即可
void solve(){
	long long h,w,s;
	cin>>h>>w>>s;
	long long ans=inf;
	// 枚举行数 a，ceil(h/a) 只有 O(√h) 种取值，按块枚举
	for(long long l=1,r;l<=h;l=r+1){
		long long c=(h+l-1)/l;            // c = ceil(h/l)，这一整块的 ceil(h/a) 都等于 c
		r=(c==1)?h:(h-1)/(c-1);           // 这一块的右端点
		long long K=s/c;                  // 每列高度不能超过 K
		if(K==0)continue;                 // 这一块连一格都放不下，跳过
		long long cols=(w+K-1)/K;         // 需要的最少列数 = ceil(w/K)
		ans=min(ans,l+cols-2);            // 代价 = (a-1)+(b-1)；块内 a 越小越好，取左端点 l
	}
	cout<<ans<<'\n';
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int t = 1;
	cin >> t;
	while (t--){
		solve();
	}
//	system("x-www-browser https://ys.mihoyo.com/");
//	cout << fixed << setprecision(10) << x << '\n';
	return 0;
}
/*
5
2 2 1
1 7 2
4 4 17
4 4 15
120 216 34
// 2
// 3
// 0
// 1
// 55

套路：
1. floor 分块：for (l=1; l<=n; l=r+1) { v=n/l; r=n/v; ... }
2. ceil  分块：v=ceil(n/l); r=(v==1)?n:(n-1)/(v-1);
3. 块内取值恒定，通常取左端点 l 就是最优；
4. 复杂度 O(√n) 一组，t 组共 O(t√n)。
*/
