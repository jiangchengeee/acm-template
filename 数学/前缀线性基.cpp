#include<iostream>
#include<stack>
#include<string>
#include<set>
#include<algorithm>
#include<queue>
#include<map>
#include<vector>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<random>
#include<cmath>
#include <functional>
#include<cctype>
#include<bitset>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
//#define int long long
mt19937_64 gen(12345);
const int N=5e5+5;
int n,q,cnt,root[N],last[N];
int ls[N<<6],rs[N<<6],w[N<<6],a[N];
int update(int lu,int l,int r,int x){
	int u=++cnt;
	ls[u]=ls[lu],rs[u]=rs[lu],w[u]=w[lu];w[u]++;
	if(l==r)return u;
	int mid=(l+r)>>1;
	if(x<=mid)ls[u]=update(ls[lu],l,mid,x);
	else rs[u]=update(rs[lu],mid+1,r,x);
	return u;
}
int query(int u1,int u2,int l,int r,int x){
	if(l>=x)return 0;
	if(r<x)return w[u2]-w[u1];
	int mid=(l+r)>>1;
	return query(ls[u1],ls[u2],l,mid,x)+query(rs[u1],rs[u2],mid+1,r,x);
}
void solve(){
	cnt=0;
	cin>>n>>q;
	vector<vector<int>>f(n+1);
	vector<vector<int>>basis(n+1,vector<int>(20,0));
	vector<vector<int>>pos(n+1,vector<int>(20,0));
	map<int,int>mp;
	up(i,1,n){cin>>a[i];last[a[i]]=0;}
	up(i,1,n-1){
		int u,v;cin>>u>>v;
		f[u].push_back(v);
		f[v].push_back(u);
	}
	int tot=0;
	vector<int>L(n+1,0),R(n+1,0);
	auto insert=[&](int p,int x)->void{
		basis[p]=basis[p-1];
		pos[p]=pos[p-1];
		int tmp=p;
		down(i,20,0)if((x>>i)&1){
			if(!basis[p][i]){
				basis[p][i]=x;
				pos[p][i]=tmp;
				return ;
			}	
			if(tmp>pos[p][i]){
				swap(tmp,pos[p][i]);
				swap(x,basis[p][i]);
			}                
			x^=basis[p][i];
		}
	};
	auto dfs=[&](auto &&self,int u,int fa)->void{
		L[u]=++tot;
		insert(tot,a[u]);
		if(last[mp[a[u]]])root[tot]=update(root[tot-1],0,n,last[mp[a[u]]]);
		else root[tot]=update(root[tot-1],0,n,0);	
		last[mp[a[u]]]=tot;	
		for(auto v:f[u])if(v!=fa){
			self(self,v,u);
		}
		R[u]=tot;
	};
	dfs(dfs,1,-1);
	int lastans=0;
	while(q--){
		int u;
		cin>>u;
		u=((lastans^u)%n+1);
//		cout<<u<<'\n';
		int l=L[u],r=R[u];
		int k=query(root[l-1],root[r],0,n,l);
//		cout<<k<<'\n';
		lastans=k;
		down(i,31,0)if((k>>i)&1){
			if(basis[r][i]&&pos[r][i]>=l){
				k^=basis[r][i];
			}
		}
		if(k==0)cout<<"your shine your be!\n";
		else cout << "-1\n";
	}
}

signed main() 
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int t = 1;
	cin >> t;
	while (t--){
		solve();
	}
//	system("x-www-browser https://ys.mihoyo.com/");
	return 0;
}
/*
1
5 3
4 3 2 0 0
1 4
1 3
2 1
1 5
4
1
5

*/
