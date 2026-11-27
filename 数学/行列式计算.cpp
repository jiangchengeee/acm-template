#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long
mt19937_64 gen(12345);
const int N=5e5+5,mod=1e9+7,inf=1e9+7;
int n,m,q,k;
int a[N],b[N],c[N],d[N];
int ksm(int a,int n,int p){//快速幂
	int res=1;a=(a%p+p)%p;
	while(n){
		if(n&1)res=res*a%p;
		n>>=1;a=a*a%p;
	}
	return res;
}
// 路径计数 + 行列式：统计「每条路径取一个点、不同路径互不相交」的方案数（CF167E）
// 对每条源点跑一遍 DAG 上的路径数 DP，建成 k*k 矩阵，再在模 p 下算行列式
void solve(){
	int p;	
	cin>>n>>m>>p;
	vector<vector<int>>f(n+1);
	vector<int>from,to,ord;//源点汇点
	vector<int>ind(n+1,0);
	for(int i=1;i<=m;++i){
		int u,v;
		cin>>u>>v;
		f[u].push_back(v);
		ind[v]++;
	}
	queue<int>q;
	for(int i=1;i<=n;i++){
		if(!ind[i])q.push(i),from.push_back(i);
		if(f[i].empty())to.push_back(i);
	}
	int k=from.size();
	vector<vector<int>>a(k+1,vector<int>(k+1,0));//行列式
	while(!q.empty()){
		int u=q.front();q.pop();ord.push_back(u);
		for(auto v:f[u]){
			if(!--ind[v])q.push(v);
		}
	}
	vector<int>dp(n+1,0);
	for(int i=1;i<=k;i++){
		fill(dp.begin(),dp.end(),0);
		dp[from[i-1]]=1;
		for(auto u:ord){
			for(auto v:f[u])(dp[v]+=dp[u])%=p;
		}
		for(int j=1;j<=k;j++)a[i][j]=dp[to[j-1]];
	}
	auto calc=[&]()->int{//k*k行列式计算
	int ans=1;
		for(int i=1;i<=k;i++){
			for(int j=i+1;j<=k;j++)if(a[j][i]){
				swap(a[i],a[j]);//交换两行
				ans=(p-ans)%p;//行列式值取负
				break;
			}
			
			ans=ans*a[i][i]%p;
			int inv=ksm(a[i][i],p-2,p);
			for(int j=i+1;j<=k;j++)if(a[j][i]){
				int t=p-a[j][i]*inv%p;// 计算消元系数 t = -a[j][i] / a[i][i]	,t = - (a[j][i] * inv)
				
				for(int r=i;r<=k;++r){
					a[j][r]=(a[j][r]+t*a[i][r])%p;// 执行行变换：Row_j = Row_j + t * Row_i
				}
			}			
		}
		return ans;
	};
	cout<<calc()<<'\n';
}
signed main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
//    cin >> t;
    while (t--){
		solve();
    }
//    system("x-www-browser https://ys.mihoyo.com/");
    return 0;
}
/*
4 3 998244353
1 3
1 4
2 4
// 1

题面：CF167E Wizards and Bets —— 数「每条路径取一个点、不同路径互不相交」的方案数，
由 Lindstrom-Gessel-Viennot，它等于「路径数矩阵」的行列式，在模 p 下算。

要点：
1. 先拓扑排序，对每个源点跑一遍路径数 DP，得到 k*k 的矩阵（k = 源点个数 = 汇点个数）；
2. 行列式用「辗转相除式」高斯消元：第 i 列下面有非零就交换两行并给答案取负；
3. p 不一定是质数时不能求逆元，要用 gcd 消元（本题 p 是质数，所以直接 ksm 求逆）；
4. 源点数 != 汇点数时题目无解（矩阵不是方阵），本题保证相等。
*/
