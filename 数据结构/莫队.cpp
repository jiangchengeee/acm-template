#include <bits/stdc++.h>
using namespace std;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
mt19937_64 gen(12345);
const int N=5e5+5,mod=998244353,inf=1e18+7;;
int n,m,q,k;
int a[N],b[N],c[N],d[N];
struct node {
    int l, r, id;
    int blk;
    friend bool operator<(const node& a, const node& b) {
        if (a.blk != b.blk) {
            return a.blk < b.blk;
        }
        return (a.blk & 1) ? (a.r < b.r) : (a.r > b.r);
    }
};
void solve(){
	cin>>n;
	up(i,1,n)cin>>a[i];
	cin>>q;
	vector<node>arr(q+1);
	vector<int>res(q+1);
	vector<int>vis(n+1,0);
	int B = sqrt(n);
	for (int i = 1; i <= q; ++i) {
		cin >> arr[i].l >> arr[i].r;
		arr[i].id = i;
		arr[i].blk = arr[i].l / B;
	}
	sort(arr.begin()+1,arr.end());
	int ans=0;
	auto add=[&](int x)->void{
		vis[a[x]]++;
		if(vis[a[x]]%2==0)ans++;
	};
	auto del=[&](int x)->void{
		vis[a[x]]--;
		if(vis[a[x]]%2==1)ans--;
	};
	int l=1,r=0;
	up(i,1,q){
		while(r<arr[i].r)add(++r);
		while(l>arr[i].l)add(--l);

		while(r>arr[i].r)del(r--);
		while(l<arr[i].l)del(l++);
		res[arr[i].id]=ans;
	}
	up(i,1,q)cout<<res[i]<<'\n';

}