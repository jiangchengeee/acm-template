#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
const int N=2e5+5;
// 树链剖分：改点权 / 查路径和 / 查子树和，全部是 O(log^2 n)
int n,m,rt,mod_;
vector<int> g[N];
int a[N],fa[N],dep[N],sz[N],son[N],top[N],dfn[N],rnk[N],cnt;
void dfs1(int u,int f){//求父亲、深度、子树大小、重儿子
	fa[u]=f,dep[u]=dep[f]+1,sz[u]=1;
	int mx=0;
	for(int v:g[u])if(v!=f){
		dfs1(v,u),sz[u]+=sz[v];
		if(sz[v]>mx)mx=sz[v],son[u]=v;
	}
}
void dfs2(int u,int tp){//给每个点分配 dfn，同一条链上连续
	top[u]=tp,dfn[u]=++cnt,rnk[cnt]=u;
	if(!son[u])return;
	dfs2(son[u],tp);//先走重儿子，保证重链连续
	for(int v:g[u])if(v!=fa[u]&&v!=son[u])dfs2(v,v);//轻儿子自己开一条链
}
// ---------- 线段树维护 dfn 序 ----------
int sum[N<<2],tag[N<<2];
void build(int u,int l,int r){
	if(l==r){sum[u]=a[rnk[l]]%mod_;return;}
	int mid=(l+r)>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
	sum[u]=(sum[u<<1]+sum[u<<1|1])%mod_;
}
void pushdown(int u,int l,int r){
	if(!tag[u])return;
	int mid=(l+r)>>1;
	sum[u<<1]=(sum[u<<1]+tag[u]*(mid-l+1))%mod_,tag[u<<1]=(tag[u<<1]+tag[u])%mod_;
	sum[u<<1|1]=(sum[u<<1|1]+tag[u]*(r-mid))%mod_,tag[u<<1|1]=(tag[u<<1|1]+tag[u])%mod_;
	tag[u]=0;
}
void update(int u,int l,int r,int ql,int qr,int v){
	if(ql<=l&&r<=qr){
		sum[u]=(sum[u]+v*(r-l+1))%mod_,tag[u]=(tag[u]+v)%mod_;
		return;
	}
	pushdown(u,l,r);
	int mid=(l+r)>>1;
	if(ql<=mid)update(u<<1,l,mid,ql,qr,v);
	if(qr>mid)update(u<<1|1,mid+1,r,ql,qr,v);
	sum[u]=(sum[u<<1]+sum[u<<1|1])%mod_;
}
int query(int u,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return sum[u];
	pushdown(u,l,r);
	int mid=(l+r)>>1,res=0;
	if(ql<=mid)res+=query(u<<1,l,mid,ql,qr);
	if(qr>mid)res+=query(u<<1|1,mid+1,r,ql,qr);
	return res%mod_;
}
// ---------- 树上操作 ----------
void path_add(int u,int v,int w){
	while(top[u]!=top[v]){//把较深的链整段处理掉
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		update(1,1,n,dfn[top[u]],dfn[u],w);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])swap(u,v);
	update(1,1,n,dfn[u],dfn[v],w);//同一条链上，u 是 LCA
}
int path_sum(int u,int v){
	int res=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		res+=query(1,1,n,dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])swap(u,v);
	res+=query(1,1,n,dfn[u],dfn[v]);
	return res%mod_;
}
int sub_sum(int u){return query(1,1,n,dfn[u],dfn[u]+sz[u]-1);}//子树在 dfn 上是连续一段
void solve(){
	cin>>n>>m>>rt>>mod_;
	up(i,1,n)cin>>a[i];
	up(i,1,n-1){
		int u,v;cin>>u>>v;
		g[u].push_back(v),g[v].push_back(u);
	}
	dfs1(rt,0),dfs2(rt,rt);
	build(1,1,n);
	while(m--){
		int op;cin>>op;
		if(op==1){
			int u,v,w;cin>>u>>v>>w;
			path_add(u,v,w);
		}else if(op==2){
			int u,v;cin>>u>>v;
			cout<<path_sum(u,v)<<'\n';
		}else if(op==3){
			int u,w;cin>>u>>w;
			update(1,1,n,dfn[u],dfn[u]+sz[u]-1,w);
		}else{
			int u;cin>>u;
			cout<<sub_sum(u)<<'\n';
		}
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
5 5 1 998244353
1 2 3 4 5
1 2
1 3
3 4
3 5
2 2 4
1 2 4 1
2 2 4
3 3 2
4 1
// 9
// 12
// 9

要点：
1. dfs1 求重儿子，dfs2 先走重儿子保证每条重链的 dfn 连续；
2. 路径 u-v：两条链不停往上跳，每次处理 dfn[top[u]]..dfn[u]；
3. 子树是 dfn 上连续的一段 [dfn[u], dfn[u]+sz[u]-1]；
4. 把线段树换成"区间加 + 区间和"，就是板子；换成区间 max/赋值的也同理。
*/
