#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
mt19937_64 gen(12345);
const int N=5e4+5,mod=998244353,inf=1e9+7;
int n,m,q,k,cnt;
int p[N],mu[N],pre[N];//mu:莫比乌斯函数 pre:mu的前缀和
bool vis[N];
void init(int n)//线性筛mu
{
	mu[1]=1;
	up(i,2,n){
		if(!vis[i])p[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*p[j]<=n;j++){
			vis[i*p[j]]=1;
			if(i%p[j]==0){mu[i*p[j]]=0;break;}//含平方因子
			mu[i*p[j]]=-mu[i];
		}
	}
	up(i,1,n)pre[i]=pre[i-1]+mu[i];
}
int query(int n,int m,int k)//求 sum sum [gcd(i,j)==k]
{//把k除掉，再用 [n==1]=sum_{d|n} mu(d) 反演
	n/=k,m/=k;
	if(n>m)swap(n,m);
	int res=0;
	for(int l=1,r;l<=n;l=r+1){//整除分块
		r=min(n/(n/l),m/(m/l));
		res+=(pre[r]-pre[l-1])*(n/l)*(m/l);
	}
	return res;
}
void solve(){
	cin>>n>>m>>k;
	cout<<query(n,m,k)<<'\n';//P3455
}

signed main() 
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	init(N-5);
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
2 2 1
4 6 2
// 3
// 5

P3455 [POI2007] ZAP-Queries
*/
