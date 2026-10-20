#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
mt19937_64 gen(12345);
const int N=1e5+5,mod=998244353,inf=1e9+7;
int n,L;
int a[N],m[N];//a:余数 m:模数 L:合并后的总模数
int exgcd(int a,int b,int &x,int &y)
{
	if(b==0){x=1,y=0;return a;}
	int d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
int norm(int x,int p){return (x%p+p)%p;}//归一到[0,p)
int addm(int a,int b,int p){return a>=p-b?a-(p-b):a+b;}//要求a,b<p
int mul(int a,int b,int p){return (__int128)norm(a,p)*norm(b,p)%p;}//防爆乘（先归一化，exgcd出来的系数可能是负的）
int crt()//朴素CRT，要求模数两两互质
{
	int M=1,res=0;
	up(i,1,n)M*=m[i];
	up(i,1,n){
		int Mi=M/m[i],x,y;
		exgcd(Mi,m[i],x,y);//Mi*x+m[i]*y=1，x即逆元
		res=addm(res,mul(mul(norm(a[i],M),Mi,M),norm(x,m[i]),M),M);
	}
	L=M;
	return res;//x=sum(a[i]*Mi*inv(Mi))
}
int excrt()//模数任意，无解返回-1，通解x+k*L
{
	int x=0,M=1;
	up(i,1,n){
		int t,s;
		int g=exgcd(M,m[i],t,s);//M*t+m[i]*s=g
		int c=norm(a[i]-x,m[i]);
		if(c%g)return -1;//裴蜀定理：g不整除c则无解
		int M2=M/g*m[i];//lcm，先除后乘
		x=addm(norm(x,M2),mul(M,mul(t,c/g,m[i]/g),M2),M2);
		M=M2;
	}
	L=M;
	return x;
}
void solve(){
	cin>>n;
	up(i,1,n)cin>>a[i]>>m[i];
	int x=excrt();//互质时直接crt()
	if(x==-1)cout<<-1<<'\n';
	else cout<<x<<'\n';
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
	return 0;
}
/*
3
2 3
3 5
2 7
// 23

3
2 4
3 6
2 5
// -1

P1495 曹冲养猪 P4777 扩展中国剩余定理 P3868 猜数字 P4774 屠龙勇士 P2480 古代猪文
*/
