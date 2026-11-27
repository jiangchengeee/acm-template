#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
mt19937_64 gen(12345);
const int N=2e5+5,M=1e6+5,INF=0x3f3f3f3f3f3f3f3f;;
int n,m,q,k,s,t;
// 邻接表存边，从 2 开始编号，反向边就是 i^1
int head[N],ecnt=1;
struct Edge{int to,cap,nxt;}e[M];
void add_edge(int u,int v,int c){
	e[++ecnt]={v,c,head[u]},head[u]=ecnt;
	e[++ecnt]={u,0,head[v]},head[v]=ecnt;
}
int dep[N],cur[N];
bool bfs(){//分层
	up(i,0,n)dep[i]=-1;
	queue<int>q;q.push(s),dep[s]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].cap>0&&dep[v]==-1)dep[v]=dep[u]+1,q.push(v);
		}
	}
	return dep[t]!=-1;
}
int dfs(int u,int flow){//沿分层图推流，当前弧优化
	if(u==t)return flow;
	for(int &i=cur[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(e[i].cap>0&&dep[v]==dep[u]+1){
			int f=dfs(v,min(flow,e[i].cap));
			if(f){e[i].cap-=f,e[i^1].cap+=f;return f;}
		}
	}
	return 0;
}
int dinic(){
	int flow=0;
	while(bfs()){
		up(i,0,n)cur[i]=head[i];
		int f;
		while((f=dfs(s,INF)))flow+=f;
	}
	return flow;
}
void solve(){
	cin>>n>>m>>s>>t;
	up(i,1,m){
		int u,v,c;cin>>u>>v>>c;
		add_edge(u,v,c);
	}
	cout<<dinic()<<'\n';
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
4 5 1 4
1 2 3
1 3 2
2 3 1
2 4 2
3 4 3
// 5

要点：
1. 边从 2 开始编号，反向边是 i^1，add_edge 同时建正反两条；
2. bfs 分层，dfs 只沿 dep+1 的边推流，当前弧 cur[] 避免重复扫；
3. 复杂度 O(V^2 E)（一般远快于这个上界，单位容量图 O(EsqrtV)）；
4. 最大流 = 最小割（跑完后的残留网络就是从 s 可达的集合）。
*/
