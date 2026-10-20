#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long
mt19937_64 gen(12345);
const int N=5e5+5,mod=1e9+7,inf=1e9+7;
int n,m,q,k;
int a[N],b[N],c[N],d[N];
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
https://codeforces.com/contest/167/problem/E

*/
