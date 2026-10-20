#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
mt19937_64 gen(12345);
const int N=1e6+5,INF=1e18;
int n,m,timer;
int A[N],C[N];//A[i]=前i个里(红-黄)  C[i]=前i个里(红-蓝)
int dp[N];//dp[i]=前i个位置能得到的最大红色长度
int L[N],R[N];//左半、右半的下标，按A排序后使用
bool cmpA(int x,int y){return A[x]<A[y];}
//带时间戳的前缀最大值树状数组：max没法删除，用timer代替清空
int bit[2*N],vis[2*N];
void upd(int x,int v)
{
	for(;x<=m;x+=x&-x){
		if(vis[x]!=timer)vis[x]=timer,bit[x]=v;//本轮第一次碰到这个位置
		else bit[x]=max(bit[x],v);
	}
}
int qry(int x)
{
	int res=-INF;
	for(;x;x-=x&-x)if(vis[x]==timer)res=max(res,bit[x]);
	return res;
}
/*
 * 区间 (k,i] 是红色  <=>  段内 红>=黄 且 红>=蓝  <=>  A[i]>=A[k] 且 C[i]>=C[k]
 *
 * dp[i] = max( dp[i-1] ,                                            // 最后一段不是红色，白扔一格
 *              i + max{dp[k]-k : k<i 且 A[k]<=A[i] 且 C[k]<=C[i]} ) // 最后一段 (k,i] 是红色
 *
 * 转移形状是"左边的 k 更新右边的 i"，于是用 CDQ 分治：先算左半，再用左半更新右半，最后算右半内部。
 * 更新时 k<i 已自动满足，只剩 A、C 两维偏序 —— 两半按 A 排序后双指针，
 * 用树状数组按 C 查"前缀最大 dp[k]-k"。总复杂度 O(n log^2 n)。
 */
void cdq(int l,int r)
{
	if(l==r){//递归到单点：所有用到它的转移都已经做完了，只差"最后一段不是红色"这一条
		if(l)dp[l]=max(dp[l],dp[l-1]);
		return;
	}
	int mid=(l+r)>>1;
	cdq(l,mid);//第一步：先把左半的 dp 全部算出来（后面要拿它们当转移来源）

	//第二步：用左半的 k 属于 [l,mid] 去更新右半的 i 属于 [mid+1,r]
	int p=0,q=0;
	up(i,l,mid)L[p++]=i;
	up(i,mid+1,r)R[q++]=i;
	sort(L,L+p,cmpA);//两半都按 A 从小到大排，方便双指针
	sort(R,R+q,cmpA);

	timer++;//开一轮新的树状数组（时间戳+1，等价于清空）
	int ptr=0;
	up(j,0,q-1){
		int i=R[j];
		//把所有 A[k]<=A[i] 的 k 插进树状数组：下标是 C[k]，存 dp[k]-k
		while(ptr<p&&A[L[ptr]]<=A[i]){
			int k=L[ptr++];
			upd(C[k]+n+1,dp[k]-k);
		}
		//此时树状数组里全是 A[k]<=A[i] 的 k，查 C[k]<=C[i] 的最大 dp[k]-k 即为最优来源
		int best=qry(C[i]+n+1);
		if(best>-INF)dp[i]=max(dp[i],i+best);
	}

	cdq(mid+1,r);//第三步：再算右半内部的转移
}
void solve(){
	cin>>n;
	up(i,1,n){
		int r,y,b;cin>>r>>y>>b;
		A[i]=A[i-1]+r-y;
		C[i]=C[i-1]+r-b;
	}
	m=2*n+2;//树状数组下标 C[i]+n+1 落在 [1,2n+1]
	up(i,0,n)dp[i]=-INF;
	dp[0]=0;
	cdq(0,n);
	cout<<dp[n]<<'\n';
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
////    system("x-www-browser https://ys.mihoyo.com/");
    return 0;
}
/*
10
1 0 0
0 1 1
0 1 1
1 1 0
0 1 1
1 0 1
0 1 0
0 1 1
1 1 1
1 0 1
// 7

n=1e6 实测约 0.7s，内存约 35MB（要开 -O2）
*/
