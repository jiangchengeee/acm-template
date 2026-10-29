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

// 收益函数：选位置 x 时能拿到的收益。赛时把这里换成题目给的公式
// 凸函数（中间低）：到所有点的距离和
double gain(double x){
	double s=0;
	up(i,1,n)s+=fabs(a[i]-x);
	return s;
}
// 凹函数（中间高）：负的平方偏差和
double gain2(double x){
	double s=0;
	up(i,1,n)s-=(a[i]-x)*(a[i]-x);
	return s;
}

void solve(){
	cin>>n;
	up(i,1,n)cin>>a[i];

	// ============ 1. 凸函数：三分求收益最小的点 ============
	// 凸函数的极小值点（例如距离和最小 = 中位数）
	double L=-1e9,R=1e9;
	up(it,1,100){
		double m1=L+(R-L)/3,m2=R-(R-L)/3;
		if(gain(m1)<gain(m2))R=m2;    //极小值在 [L,m2]
		else L=m1;                     //极小值在 [m1,R]
	}
	double x1=(L+R)/2;
	printf("凸(实) 最优点 x=%.6f  收益=%.6f\n",x1,gain(x1));

	// ============ 2. 凹函数：三分求收益最大的点 ============
	// 和上面只差一个比较符号：
	//   求最小：gain(m1) < gain(m2) → R = m2
	//   求最大：gain(m1) > gain(m2) → R = m2
	L=-1e9,R=1e9;
	up(it,1,100){
		double m1=L+(R-L)/3,m2=R-(R-L)/3;
		if(gain2(m1)>gain2(m2))R=m2;   //极大值在 [L,m2]
		else L=m1;
	}
	double x2=(L+R)/2;
	printf("凹(实) 最优点 x=%.6f  收益=%.6f\n",x2,gain2(x2));

	// ============ 3. 答案要求整数：用整数三分 ============
	// 别用实数三分再取整，取整可能落到次优；整数三分先收缩到长度<=2 再暴力
	long long lo=-1000000000,hi=1000000000;
	while(hi-lo>2){
		long long m1=lo+(hi-lo)/3,m2=hi-(hi-lo)/3;
		if(gain(m1)<gain(m2))hi=m2;    //求最大就把 < 改成 >
		else lo=m1;
	}
	long long bp=lo;
	up(i,lo,hi)if(gain(i)<gain(bp))bp=i;
	printf("凸(整) 最优点 x=%lld  收益=%.6f\n",bp,gain(bp));
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
5
1 3 7 9 11
// 凸(实) 最优点 x=7.000000  收益=16.000000     距离和最小 = 中位数
// 凹(实) 最优点 x=6.200000  收益=-68.800000    负平方偏差和最大 = 平均值
// 凸(整) 最优点 x=7  收益=16.000000

要点：
1. gain(x) 就是"选位置 x 时的收益"，凸函数求最小、凹函数求最大，只差一个比较符号；
2. 实数域三分写死 100 次迭代即可；
3. 答案要是整数就用整数三分（收缩到长度<=2 再暴力），别实数三分后取整；
4. 三分只对单峰函数有效，多峰的收益函数会停在局部最优。
*/
