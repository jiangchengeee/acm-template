#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
mt19937_64 gen(12345);
const int N=2e5+5,M=1e6+5,INF=0x3f3f3f3f3f3f3f3f;;
int n,m,q,k,s,t;
int head[N],ecnt=1;
struct Edge{int to,cap,cost,nxt;}e[M];
void add_edge(int u,int v,int c,int w){
	e[++ecnt]={v,c,w,head[u]},head[u]=ecnt;
	e[++ecnt]={u,0,-w,head[v]},head[v]=ecnt;//反向边容量为 0、费用取反
}
int dis[N],inq[N],pre[N];
bool spfa(){//沿费用找一条最短的增广路
	up(i,0,n)dis[i]=INF,inq[i]=0,pre[i]=-1;
	queue<int>q;q.push(s),dis[s]=0,inq[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop(),inq[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].cap>0&&dis[v]>dis[u]+e[i].cost){
				dis[v]=dis[u]+e[i].cost,pre[v]=i;
				if(!inq[v])inq[v]=1,q.push(v);
			}
		}
	}
	return dis[t]!=INF;
}
void mcmf(int &flow,int &cost){//最小费用最大流
	flow=cost=0;
	while(spfa()){
		int f=INF;
		for(int v=t;v!=s;v=e[pre[v]^1].to)f=min(f,e[pre[v]].cap);//找这一条路的瓶颈
		for(int v=t;v!=s;v=e[pre[v]^1].to)e[pre[v]].cap-=f,e[pre[v]^1].cap+=f;
		flow+=f,cost+=f*dis[t];
	}
}
void solve(){
	cin>>n>>m>>s>>t;
	up(i,1,m){
		int u,v,c,w;cin>>u>>v>>c>>w;
		add_edge(u,v,c,w);
	}
	int flow,cost;
	mcmf(flow,cost);
	cout<<flow<<" "<<cost<<'\n';
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
1 2 2 1
1 3 1 2
2 3 1 1
2 4 1 3
3 4 2 1
// 3 10

要点：
1. 每次沿"费用最短路"增广，直到没有增广路，得到的就是最小费用最大流；
2. 反向边费用取反，才能"退流"；
3. SPFA 复杂度 O(VE)，有负权也能跑；点数大且费用非负时换 Dijkstra + 势（Johnson）更快；
4. 只要求"不超过流量 F 的最小费用"时，增广到 flow>=F 就停。
*/
