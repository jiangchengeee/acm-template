#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
const int N=2e5+5;
vector<int> g[N];
int dfn[N],low[N],stk[N],instk[N],scc[N],sz[N];
int tim,top,cnt;
void tarjan(int u){
	dfn[u]=low[u]=++tim;
	stk[++top]=u,instk[u]=1;
	for(int v:g[u]){
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(instk[v])low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){//u 是这个强连通分量的根
		cnt++;
		int x;
		do{
			x=stk[top--],instk[x]=0;
			scc[x]=cnt,sz[cnt]++;
		}while(x!=u);
	}
}
void solve(){
	int n,m;
	cin>>n>>m;
	up(i,1,m){
		int u,v;cin>>u>>v;
		g[u].push_back(v);
	}
	up(i,1,n)if(!dfn[i])tarjan(i);
	// 输出：每个点所属的强连通分量编号（Tarjan 的编号是逆拓扑序）
	up(i,1,n)cout<<scc[i]<<" \n"[i==n];
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
4 4
1 2
2 3
3 1
3 4
// 2 2 2 1     （1,2,3 是一个 SCC，4 单独）

要点：
1. dfn 是时间戳，low 是能回溯到的最早时间戳；同一个 SCC 的 low 判定是 dfn[u]==low[u]；
2. scc 编号按"出栈顺序"给出，是缩点后 DAG 的逆拓扑序，做 DP 时直接用；
3. 缩点：把每个 scc 当一个点，边去重后原图变成 DAG，可以拓扑 DP；
4. 割点/桥：Tarjan 稍改一下——桥是 low[v] > dfn[u]，割点是 low[v] >= dfn[u]（且不是根）。
*/
