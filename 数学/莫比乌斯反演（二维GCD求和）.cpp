#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
mt19937_64 gen(12345);
const int N=1e6+5,mod=998244353,inf=1e9+7;
int n,m,q,k,cnt;
int p[N],phi[N],pre[N];//phi:欧拉函数 pre:phi的前缀和
bool vis[N];
void init(int n)//线性筛phi
{
	phi[1]=1;
	up(i,2,n){
		if(!vis[i])p[++cnt]=i,phi[i]=i-1;
		for(int j=1;j<=cnt&&i*p[j]<=n;j++){
			vis[i*p[j]]=1;
			if(i%p[j]==0){phi[i*p[j]]=phi[i]*p[j];break;}//p[j]|i，指数+1
			phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}
	up(i,1,n)pre[i]=pre[i-1]+phi[i];
}
int gcdsum(int n,int m)//求 sum_{i<=n} sum_{j<=m} gcd(i,j)
{//用 gcd(i,j)=sum_{d|gcd(i,j)} phi(d)，交换求和次序
	if(n>m)swap(n,m);
	int res=0;
	for(int l=1,r;l<=n;l=r+1){//整除分块
		r=min(n/(n/l),m/(m/l));
		res+=(pre[r]-pre[l-1])*(n/l)*(m/l);
	}
	return res;
}
void solve(){
	cin>>n>>m;
	cout<<gcdsum(n,m)<<'\n';//P2398只有n，读两次n即可
}

signed main() 
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	init(N-5);
	int t = 1;
//	cin >> t;
	while (t--){
		solve();
	}
//	system("x-www-browser https://ys.mihoyo.com/");
	return 0;
}
/*
2 2
// 5

P2398 GCD SUM P2568 GCD
*/
