#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
mt19937_64 gen(12345);
const int N=1e6+5,mod=998244353,inf=1e9+7;
int n,m,p,fac[N];//fac:阶乘，Lucas用，要求p<N
int ksm(int a,int b,int p)
{
	int res=1;
	while(b){
		if(b&1)res=res*a%p;
		a=a*a%p;
		b>>=1;
	}
	return res;
}
int exgcd(int a,int b,int &x,int &y)
{
	if(b==0){x=1,y=0;return a;}
	int d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
int norm(int x,int p){return (x%p+p)%p;}
int inv(int a,int p){int x,y;exgcd(a,p,x,y);return norm(x,p);}
int isprime(int x)
{
	if(x<2)return 0;
	for(int i=2;i*i<=x;i++)if(x%i==0)return 0;
	return 1;
}
int C(int n,int m,int p)//n,m<p，用阶乘+费马小定理
{
	if(m>n)return 0;
	return fac[n]*ksm(fac[m],p-2,p)%p*ksm(fac[n-m],p-2,p)%p;
}
int lucas(int n,int m,int p)//p必须是素数，用前需init(p)
{
	if(m==0)return 1;
	return C(n%p,m%p,p)*lucas(n/p,m/p,p)%p;
}
int facpk(int n,int p,int pk)//n!去掉所有p因子后mod pk
{
	if(n==0)return 1;
	int res=1;
	up(i,1,pk)if(i%p)res=res*i%pk;//一个完整周期的积
	res=ksm(res,n/pk,pk);
	up(i,1,n%pk)if(i%p)res=res*i%pk;//零头
	return res*facpk(n/p,p,pk)%pk;
}
int Cpk(int n,int m,int p,int pk)//C(n,m) mod pk
{
	if(n<m)return 0;
	int e=0;
	for(int i=n;i;i/=p)e+=i/p;
	for(int i=m;i;i/=p)e-=i/p;
	for(int i=n-m;i;i/=p)e-=i/p;//e=v_p(n!)-v_p(m!)-v_p((n-m)!)
	int a=facpk(n,p,pk),b=facpk(m,p,pk),c=facpk(n-m,p,pk);
	return a*inv(b,pk)%pk*inv(c,pk)%pk*ksm(p,e,pk)%pk;
}
int exlucas(int n,int m,int mod)//mod任意，要求分解出的pk不大
{
	if(n<m)return 0;
	int res=0,M=1,x=mod;//已合并的答案 res mod M
	for(int i=2;i*i<=x;i++){
		if(x%i)continue;
		int pk=1;
		while(x%i==0)x/=i,pk*=i;
		int t=norm(Cpk(n,m,i,pk)-res,pk)*inv(M%pk,pk)%pk;
		res+=M*t,M*=pk,res%=M;
	}
	if(x>1){//剩下一个大质因子
		int pk=x;
		int t=norm(Cpk(n,m,x,pk)-res,pk)*inv(M%pk,pk)%pk;
		res+=M*t,M*=pk,res%=M;
	}
	return res;
}
void solve(){
	cin>>n>>m>>p;
	if(isprime(p)&&p<N){//素数且不太大，Lucas更快
		fac[0]=1;
		up(i,1,p-1)fac[i]=fac[i-1]*i%p;
		cout<<lucas(n,m,p)<<'\n';
	}
	else cout<<exlucas(n,m,p)<<'\n';
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
	return 0;
}
/*
2
5 3 7
6 4 9
// 3
// 6

P3807 卢卡斯定理 P4720 扩展卢卡斯定理 P2480 古代猪文
*/
