#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
const int N=2e6+5;
// 2-SAT：n 个布尔变量、m 条约束 (a or b)，判断是否有解并给出一组解
// 结点编号：变量 i（1-based）的"假"用 2(i-1)，"真"用 2(i-1)+1，共 2n 个点
vector<int> g[N];
int dfn[N],low[N],stk[N],instk[N],scc[N];
int tim,top,cnt;
void add(int u,int v){g[u].push_back(v);}
int node(int i,int v){return 2*(i-1)+v;}//v=1 表示"x_i 为真"
void tarjan(int u){
	dfn[u]=low[u]=++tim;
	stk[++top]=u,instk[u]=1;
	for(int v:g[u]){
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(instk[v])low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		cnt++;
		int x;
		do{x=stk[top--],instk[x]=0,scc[x]=cnt;}while(x!=u);
	}
}
void solve(){
	int n,m;
	cin>>n>>m;
	up(k,1,m){
		int i,a,j,b;//约束：(x_i == a) or (x_j == b)
		cin>>i>>a>>j>>b;
		add(node(i,a^1),node(j,b));//¬a -> b
		add(node(j,b^1),node(i,a));//¬b -> a
	}
	up(i,0,2*n-1)if(!dfn[i])tarjan(i);
	up(i,1,n)if(scc[node(i,0)]==scc[node(i,1)]){//x 与 ¬x 同一 SCC -> 矛盾
		cout<<"IMPOSSIBLE\n";return;
	}
	// Tarjan 的 SCC 编号是逆拓扑序，所以"真"的编号更小就取真
	up(i,1,n)cout<<(scc[node(i,1)]<scc[node(i,0)])<<" \n"[i==n];
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
3 2
1 1 2 0
2 1 3 1
// 1 1 0

要点：
1. 每条约束 (a or b) 变成两条蕴含边：¬a -> b、¬b -> a；
2. Tarjan 求 SCC，某变量的"真"和"假"在同一 SCC 里就无解；
3. 赋值：scc[真] < scc[假] 取真——Tarjan 的 SCC 编号是逆拓扑序，和 Kosaraju 相反，写反会得到错解；
4. 结点编号 0 起（2*(i-1)+v，共 2n 个），遍历区间是 [0, 2n-1]，写成 2n+1 会漏点；
5. 复杂度 O(n+m)。
*/
