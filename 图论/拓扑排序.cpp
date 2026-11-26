#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
const int N=2e5+5;
vector<int> g[N];
int deg[N];//入度
void solve(){
	int n,m;
	cin>>n>>m;
	up(i,1,m){
		int u,v;cin>>u>>v;
		g[u].push_back(v),deg[v]++;
	}
	queue<int>q;
	up(i,1,n)if(!deg[i])q.push(i);
	vector<int>ord;
	while(!q.empty()){
		int u=q.front();q.pop();
		ord.push_back(u);
		for(int v:g[u])if(!--deg[v])q.push(v);
	}
	if((int)ord.size()<n)cout<<"-1\n";//有环，无拓扑序
	else{
		for(int x:ord)cout<<x<<" \n"[x==ord.back()];
	}
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
4 3
1 2
2 3
3 4
// 1 2 3 4

要点：
1. Kahn 算法：不断取出入度为 0 的点；
2. 输出点数 < n 说明有环；
3. 字典序最小的拓扑序：把 queue 换成 priority_queue；
4. 用 bitset 优化可以做到 O(nm/64)。
*/
