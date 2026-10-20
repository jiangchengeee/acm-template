#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
int n,m,q,k,inf=1e9+7;
struct node{
	int v,w;
	friend bool operator<(node a,node b){
		return a.w>b.w;
	};
};
void solve(){
	cin>>n>>m;
	vector<vector<node>>f(n+1);
	vector<int>dis(n+1,inf),vis(n+1,0);
	up(i,1,m){
		int u,v,w;
		cin>>u>>v>>w;
		f[u].push_back({v,w});
		f[v].push_back({u,w});
	}
	dis[1]=0;
	priority_queue<node>q;
	q.push({1,0});
	while(!q.empty()){
		int u=q.top().v;
		q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(auto [v,w]:f[u])if(dis[v]>dis[u]+w){
			dis[v]=dis[u]+w;
			q.push({v,dis[v]});
		}
	}
	up(i,2,n){
		if(dis[i]!=inf)cout<<dis[i]<<'\n';
		else cout<<-1<<'\n';
	}
}
