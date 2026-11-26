#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
const int N=1e6+5,mod=1e9+7;
int fac[N],ifac[N];
int ksm(int a,int b,int p){int r=1%p;for(;b;b>>=1,a=a*a%p)if(b&1)r=r*a%p;return r;}
void init(int n){//预处理到 n，要求 mod 是素数
	fac[0]=1;
	up(i,1,n)fac[i]=fac[i-1]*i%mod;
	ifac[n]=ksm(fac[n],mod-2,mod);
	down(i,n,1)ifac[i-1]=ifac[i]*i%mod;
}
int C(int n,int m){//组合数 C(n,m)
	if(m<0||m>n)return 0;
	return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
int A(int n,int m){//排列数 P(n,m)
	if(m<0||m>n)return 0;
	return fac[n]*ifac[n-m]%mod;
}
void solve(){
	init(N-5);
	int q;
	cin>>q;
	while(q--){
		int n,m;cin>>n>>m;
		cout<<C(n,m)<<'\n';
	}
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
//	cin >> T;
	while (T--){
		solve();
	}
//	system("x-www-browser https://ys.mihoyo.com/");
	return 0;
}
/*
3
5 2
10 3
100 50
// 10
// 120
// 538992043

要点：
1. fac 阶乘、ifac 阶乘逆元，逆元用费马小定理（要求 mod 为素数）；
2. 一次预处理 O(n)，单次询问 O(1)；
3. mod 是合数时不能用这个板子，要用 Lucas（素数）或 exLucas（合数）。
*/
