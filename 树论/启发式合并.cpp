#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
mt19937_64 gen(12345);
const int N=5e5+5,mod=998244353,inf=1e9+7;;
int n,m,q,k;
int a[N],b[N],c[N],d[N];
struct orz_trie {
	int tr[N*32][2];
	int cnt[N*32];
	int tot=0;
	void init(){
		up(i,0,tot){
			tr[i][0]=tr[i][1] = 0;
			cnt[i]=0;
		}
		tot=0;
	}
	void update(int x, int delta){// delta=1 插入，delta=-1 删除
		int p=0;
		down(i,30,0){
			int bit=(x>>i)&1;
			if(tr[p][bit]==0){
				tr[p][bit]=++tot;
			}
			p=tr[p][bit];
			cnt[p]+=delta;
		}
	}
	int query(int x){
		int p=0;
		int ma=0;
		if(cnt[tr[0][0]] ==0&&cnt[tr[0][1]] == 0) return 0;// 树为空
		down(i,30,0){
			int bit=(x>>i)&1;
			if(tr[p][bit^1]&&cnt[tr[p][bit^1]]>0){
				ma|=(1<<i);
				p=tr[p][bit^1];
			} else { 
				p=tr[p][bit];
			}
		}
		return ma;
	}    
}tri;
void solve(){
	cin>>n;
	up(i,1,n)cin>>a[i];
	vector<vector<int>>f(n+1);
	up(i,1,n-1){
		int u,v;cin>>u>>v;
		f[u].push_back(v);
		f[v].push_back(u);
	}
	int ans=0;  
	vector<int>sz(n+1,0),son(n+1,0),pre(n+1,0);
	auto dfs1=[&](auto &&self,int u,int fa)->void{
		sz[u]++;
		int ma=0;
		pre[u]=pre[fa]^a[u];
		for(auto v:f[u])if(v!=fa){
			self(self,v,u);
			sz[u]+=sz[v];
			if(sz[v]>ma){ma=sz[v];son[u]=v;}
		}
	};
	auto dfs2=[&](auto &&self,int u,int fa,int ok,int lca)->void{
		if(ok==0)ans=max(ans,tri.query(pre[u]^lca));
		if(ok==1||ok==-1)tri.update(pre[u],ok);
		for(auto v:f[u])if(v!=fa){
			self(self,v,u,ok,lca);
		}
	};
	auto dfs3=[&](auto &&self,int u,int fa,bool ok)->void{
		for(auto v:f[u])if(v!=fa&&v!=son[u]){
			self(self,v,u,0);// 处理轻儿子
		}
		if(son[u])self(self,son[u],u,1);// 处理重儿子
		for(auto v:f[u])if(v!=fa&&son[u]!=v){
			dfs2(dfs2,v,u,0,a[u]);// 查询
			dfs2(dfs2,v,u,1,a[u]);// 插入
		}
		tri.update(pre[u],1);// 处理自己
		ans=max(ans,tri.query(pre[u]^a[u]));    
		if(!ok){
			for(auto v:f[u])if(v!=fa)
				dfs2(dfs2,v,u,-1,0);// 清空轻儿子
			tri.update(pre[u],-1);
		}
	};
	dfs1(dfs1,1,0);
	dfs3(dfs3,1,0,1);
	cout<<ans<<'\n';
}

signed main() 
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int t = 1;
//    cin >> t;
	while (t--){
		solve();
	}
//    system("x-www-browser https://ys.mihoyo.com/");
//    cout << fixed << setprecision(10) << x << '\n';
	return 0;
}
/*
启发式合并步骤：
预处理子树大小，确定重儿子；
先递归处理轻儿子，再处理重儿子；
暴力合并轻儿子信息并统计当前点答案；
当前点为轻儿子时清空贡献。
总复杂度 O(n log n)。
*/
