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

// 题目给的函数，赛时把这里换掉即可
double f(double x){return (x-2)*(x-2)+3;}          // 凸：中间低
double g(double x){return -(x+1)*(x+1)+5;}         // 凹：中间高
double f2(double x,double y){return (x-1)*(x-1)+(y+2)*(y+2);}  // 二维凸

// 二分套三分里"固定 y 三分 x"的内层，返回最优的 x
double best_x(double y){
	double l=-10,r=10;
	up(it,1,100){
		double m1=l+(r-l)/3,m2=r-(r-l)/3;
		if(f2(m1,y)<f2(m2,y))r=m2;
		else l=m1;
	}
	return (l+r)/2;
}

void solve(){
	// ============ 1. 实数域三分：凸函数求最小值 ============
	double l=-10,r=10;
	up(it,1,100){//写死 100 次，不用管 eps
		double m1=l+(r-l)/3,m2=r-(r-l)/3;
		if(f(m1)<f(m2))r=m2;      //极小值在 [l,m2]
		else l=m1;                //极小值在 [m1,r]
	}
	double x1=(l+r)/2;
	cout<<"凸(实) "<<x1<<" "<<f(x1)<<'\n';

	// ============ 2. 实数域三分：凹函数求最大值 ============
	// 和上面只差一个比较符号：把 f(m1)<f(m2) 改成 g(m1)>g(m2)
	l=-10,r=10;
	up(it,1,100){
		double m1=l+(r-l)/3,m2=r-(r-l)/3;
		if(g(m1)>g(m2))r=m2;      //极大值在 [l,m2]
		else l=m1;
	}
	double x2=(l+r)/2;
	cout<<"凹(实) "<<x2<<" "<<g(x2)<<'\n';

	// ============ 3. 整数域三分：先收缩到长度 <= 2，再暴力 ============
	long long L=0,R=20,bf=inf,bp=L;
	while(R-L>2){
		long long m1=L+(R-L)/3,m2=R-(R-L)/3;
		if(f(m1)<f(m2))R=m2;      //求最大就把这里改成 >
		else L=m1;
	}
	up(i,L,R)if(f(i)<bf)bf=f(i),bp=i;//剩下几个点直接比
	cout<<"凸(整) "<<bp<<" "<<bf<<'\n';

	// ============ 4. 三分套三分：二维求最小值（全局最优）============
	// 外层三分 y，内层固定 y 三分 x
	double yl=-10,yr=10,y1,y2;
	up(it,1,100){
		y1=yl+(yr-yl)/3,y2=yr-(yr-yl)/3;
		double v1=f2(best_x(y1),y1),v2=f2(best_x(y2),y2);
		if(v1<v2)yr=y2;
		else yl=y1;
	}
	double yy=(yl+yr)/2,xx=best_x(yy);
	cout<<"二维   "<<xx<<" "<<yy<<" "<<f2(xx,yy)<<'\n';
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
//	system("x-www-browser https://ys.mihoyo.com/");
//	cout << fixed << setprecision(10) << x << '\n';
	return 0;
}
/*
凸(实) 2 3
凹(实) -1 5
凸(整) 2 3
二维   1 -2 0

要点：
1. 实数域：m1 = l+(r-l)/3，m2 = r-(r-l)/3，写死 100 次迭代；
   凸函数求最小用 f(m1)<f(m2) → r=m2，凹函数求最大把 < 改成 >。
2. 整数域：收缩到 R-L<=2 后暴力，避免取整漏掉最优解。
3. 二维：外层三分 y，内层固定 y 三分 x 求最优，内层的最优值就是外层的函数值。
4. 三分只对单峰（有平顶也行）函数有效，多峰会挂在局部最优。
*/
