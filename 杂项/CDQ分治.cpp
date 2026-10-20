#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
mt19937_64 gen(12345);
const int N=1e5+5,M=2e5+5;
int n,k,cnt;
struct node{int a,b,c,w,res;}p[N],t[N];//w:相同元素个数 res:被多少个点支配
int bit[M],ans[N];//ans[i]:有多少个点被恰好i个点支配
bool cmp1(node x,node y)//按a,b,c排序
{
	if(x.a!=y.a)return x.a<y.a;
	if(x.b!=y.b)return x.b<y.b;
	return x.c<y.c;
}
bool cmp2(node x,node y)//按b,c排序
{
	if(x.b!=y.b)return x.b<y.b;
	return x.c<y.c;
}
void add(int x,int v){for(;x<=k;x+=x&-x)bit[x]+=v;}
int query(int x){int res=0;for(;x;x-=x&-x)res+=bit[x];return res;}
void cdq(int l,int r)
{
	if(l==r)return;
	int mid=(l+r)>>1;
	cdq(l,mid),cdq(mid+1,r);
	sort(t+l,t+mid+1,cmp2),sort(t+mid+1,t+r+1,cmp2);
	int i=l,j=mid+1;
	for(;j<=r;j++){//双指针把左半区b<=b_j的点插入树状数组
		while(i<=mid&&t[i].b<=t[j].b)add(t[i].c,t[i].w),i++;
		t[j].res+=query(t[j].c);
	}
	up(u,l,i-1)add(t[u].c,-t[u].w);//撤销树状数组
}
void solve(){
	cin>>n>>k;
	up(i,1,n)cin>>p[i].a>>p[i].b>>p[i].c;
	sort(p+1,p+n+1,cmp1);
	up(i,1,n){//去重，相同三元组合并，w记个数
		if(i>1&&p[i].a==p[i-1].a&&p[i].b==p[i-1].b&&p[i].c==p[i-1].c)t[cnt].w++;
		else t[++cnt]=p[i],t[cnt].w=1;
	}
	cdq(1,cnt);
	up(i,1,cnt)ans[t[i].res+t[i].w-1]+=t[i].w;
	up(i,0,n-1)cout<<ans[i]<<'\n';
}

signed main() 
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int t = 1;
//	cin >> t;
	while (t--){
		solve();
	}
//	system("x-www-browser https://ys.mihoyo.com/");
	return 0;
}
/*
10 3
3 3 3
2 3 3
2 3 1
3 1 1
3 1 2
1 3 1
1 1 2
1 2 2
1 3 2
1 2 1
// 3 1 3 0 1 0 1 0 0 1（每行一个）

P3810 【模板】三维偏序（陌上花开） P3157 [CQOI2011] 动态逆序对 P2487 [SDOI2011] 拦截导弹
*/
