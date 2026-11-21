#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
mt19937_64 gen(12345);
const int N=1e6+5,inf=0x3f3f3f3f3f3f3f3f;;
int n,m,l,r;
vector<int> g[N];
int match[N];//match[v] = 右部点 v 匹配到的左部点
int vis[N],tag;//vis 记时间戳，免每次清空
bool dfs(int u){
	for(int v:g[u]){
		if(vis[v]==tag)continue;
		vis[v]=tag;
		if(!match[v]||dfs(match[v])){match[v]=u;return 1;}
	}
	return 0;
}
int hungary(){//左部点编号 1..l，右部 1..r
	int res=0;
	up(u,1,l){
		tag++;
		if(dfs(u))res++;
	}
	return res;
}
void solve(){
	cin>>l>>r>>m;//左部点、右部点、边数
	up(i,1,m){
		int u,v;cin>>u>>v;
		g[u].push_back(v);
	}
	cout<<hungary()<<'\n';
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
3 3 4
1 1
1 2
2 2
3 3
// 3

要点：
1. 只能处理二分图（左右部点分开编号）；
2. 复杂度 O(VE)，二分图点数大时用 Dinic（源点连左部、右部连汇点，容量全是 1）更快；
3. 求出来的是最大匹配，配合结论：
   最小点覆盖 = 最大匹配，最大独立集 = 点数 - 最大匹配。
*/
