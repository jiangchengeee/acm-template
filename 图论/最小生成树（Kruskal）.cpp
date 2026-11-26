#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
const int N=2e5+5;
struct Edge{int u,v,w;}e[N];
bool cmp(Edge a,Edge b){return a.w<b.w;}
int fa[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void solve(){
	int n,m;
	cin>>n>>m;
	up(i,1,m)cin>>e[i].u>>e[i].v>>e[i].w;
	sort(e+1,e+m+1,cmp);
	up(i,1,n)fa[i]=i;
	int cnt=0,sum=0;
	up(i,1,m){
		int u=find(e[i].u),v=find(e[i].v);
		if(u==v)continue;
		fa[u]=v,cnt++,sum+=e[i].w;
		if(cnt==n-1)break;
	}
	if(cnt<n-1)cout<<"NO\n";//不连通
	else cout<<sum<<'\n';
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
4 5
1 2 1
1 3 4
2 3 2
2 4 5
3 4 3
// 6

要点：
1. 按边权排序，用并查集逐条加边，不成环就加入，选够 n-1 条为止；
2. 复杂度 O(m log m)（排序），加边部分近似 O(m alpha)；
3. cnt < n-1 说明图不连通；
4. 求"次小生成树"就在 MST 上枚举非树边 + 树上倍增求路径最大值。
*/
