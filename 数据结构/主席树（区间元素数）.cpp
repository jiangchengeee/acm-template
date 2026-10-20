#include<iostream>
#include<stack>
#include<string>
#include<set>
#include<algorithm>
#include<queue>
#include<map>
#include<vector>
#include<cmath>
using namespace std;
//#define int long long
const int N=1e6+5;
int n,m,cnt,root[N],last[N];
int ls[N<<5],rs[N<<5],w[N<<5];
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
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		if(last[x])root[i]=update(root[i-1],0,n,last[x]);
		else root[i]=update(root[i-1],0,n,0);	
		last[x]=i;	
	}
	cin>>m;
	while(m--){
		int l,r;
		cin>>l>>r;
		cout<<query(root[l-1],root[r],0,n,l)<<'\n';
	}
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T=1;
    while(T--)solve();
}
/*
*/