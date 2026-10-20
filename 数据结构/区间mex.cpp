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
#include <ext/pb_ds/assoc_container.hpp> // 包含所有容器（哈希表、树、堆）
#include <ext/pb_ds/tree_policy.hpp>     // 包含树的相关策略（用于实现平衡树）
#include <ext/pb_ds/hash_policy.hpp>     // 包含哈希表的相关策略
#include <ext/pb_ds/priority_queue.hpp>  // 包含优先级队列（堆）
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
mt19937_64 gen(12345);
const int N=5e5+5,mod=998244353,inf=1e9+7;;
int n,m,q,k;
int a[N],b[N],c[N],d[N];
int gcd(int x,int y)
{
	if(y==0)return x;
	return gcd(y,x%y);
}
int ksm(int a,int n,int p)
{
	if(n<0)return 0;
	int res=1;
	while(n)
	{
		if(n&1)res=res*a%p;
		n>>=1;
		a=a*a%p;
	}
	return res;
}
struct code{
	int l,r,id;
	friend bool operator<(code a,code b){
		return a.r<b.r;
	}
}p[N];
struct node{
	int l,r,w;
}t[N<<2];
void pushup(int u){
	t[u].w=min(t[u<<1].w,t[u<<1|1].w);
}
void build(int u,int l,int r){
	t[u]={l,r,0};
	if(l==r)return ;
	int m=(l+r)>>1;
	build(u<<1,l,m),build(u<<1|1,m+1,r);
	pushup(u);
}
void update(int u,int p,int x){
	if(t[u].l==t[u].r){t[u].w=x;return ;}
	int m=(t[u].l+t[u].r)>>1;
	if(p<=m)update(u<<1,p,x);
	else update(u<<1|1,p,x);
	pushup(u);
}
int query(int u,int x){
	if(t[u].w>=x)return inf;
	if(t[u].l==t[u].r)return t[u].l;
	if(t[u<<1].w<x)return query(u<<1,x);
	return query(u<<1|1,x);
}

void solve(){
	cin>>n;
	up(i,1,n)cin>>a[i];
	cin>>m;
	vector<int>ans(m+1,0);
	up(i,1,m){
		cin>>p[i].l>>p[i].r;
		p[i].id=i;
	}
	sort(p+1,p+m+1);
	int pos=1;
	build(1,1,n);
	up(i,1,m){
		up(j,pos,p[i].r)if(a[j]<=n){
			update(1,a[j],j);
		}
//         cout<<p[i].r-p[i].l+1<<" "<<query(1,p[i].l)<<'\n';
		ans[p[i].id]=p[i].r-p[i].l+1-query(1,p[i].l);
		if(ans[p[i].id]<0)ans[p[i].id]=0;
		pos=p[i].r;
	}
	up(i,1,m)cout<<ans[i]<<'\n';
}

signed main() 
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int t = 1;
// 	cin >> t;
	while (t--){
		solve();
	}
//	system("x-www-browser https://ys.mihoyo.com/");
	return 0;
}
/*
1
3 3 2 6
2 1 2


*/
