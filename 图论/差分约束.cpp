#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
const int N=2e5+5,INF=0x3f3f3f3f3f3f3f3f;;
// 差分约束：把 x_v - x_u <= w 建成边 u -> v 权 w，跑最短路
// 有负环 -> 无解；最短路 dis[i] 就是一组可行解
int n,m;
int head[N],ecnt;
struct Edge{int to,w,nxt;}e[N*2];
void add_edge(int u,int v,int w){
	e[++ecnt]={v,w,head[u]},head[u]=ecnt;
}
int dis[N],cnt[N];
bool inq[N];
bool spfa(){
	up(i,0,n)dis[i]=INF,cnt[i]=0,inq[i]=0;
	queue<int>q;
	up(i,0,n)q.push(i),dis[i]=0,inq[i]=1;//超级源点 0 连所有点
	while(!q.empty()){
		int u=q.front();q.pop(),inq[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				if(++cnt[v]>n+1)return 0;//入队超过 n 次 -> 负环
				if(!inq[v])inq[v]=1,q.push(v);
			}
		}
	}
	return 1;
}
void solve(){
	cin>>n>>m;
	up(i,1,m){
		int u,v,w;cin>>u>>v>>w;
		add_edge(u,v,w);//x_v - x_u <= w
	}
	if(!spfa())cout<<"NO\n";//无解（负环）
	else up(i,1,n)cout<<dis[i]<<" \n"[i==n];
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
3 3
1 2 3
2 3 -2
1 3 5
// 0 0 -2

要点：
1. x_v - x_u <= w 就建 u->v 权 w，跑最短路；有负环则无解；
2. >= 约束先取负变成 <=，或者反过来求最长路；
3. 相等 x_u = x_v 拆成两条：u->v 0 和 v->u 0；
4. x_v - x_u > w 要转成 x_u - x_v < -w，即 x_u - x_v <= -w-1（整数）；
5. 用 SPFA；点数大时注意被卡，可以换 SLF 优化或 Bellman-Ford。
*/
