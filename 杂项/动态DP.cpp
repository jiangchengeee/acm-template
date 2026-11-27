#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
mt19937_64 gen(12345);
const int N=1e6+5,inf=0x3f3f3f3f3f3f3f3f;;
int n,m,q,k,mod=998244353;
int a[N],b[N],c[N],d[N];

// ================== DDP：线段树维护 2x2 矩阵连乘 ==================
// 状态 0 = 向左倒，状态 1 = 向右倒
// M[i][j] = 相邻两棍"前一棍方向 i、后一棍方向 j"是否合法（合法记 1）
// 方案数 = [1,1] * T2 * T3 * ... * Tn 的各分量和（第一根 L/R 都可，初值都为 1）
struct Mat{
	int v[2][2];
	Mat(){v[0][0]=v[0][1]=v[1][0]=v[1][1]=0;}
	static Mat I(){Mat r;r.v[0][0]=r.v[1][1]=1;return r;}
};
Mat operator*(const Mat&A,const Mat&B){
	Mat C;
	up(i,0,1)up(k,0,1)if(A.v[i][k])up(j,0,1)C.v[i][j]=(C.v[i][j]+A.v[i][k]*B.v[k][j])%mod;
	return C;
}
Mat tr[4*N];
void build(int u,int l,int r){
	if(l==r){tr[u]=Mat();return;}
	int mid=(l+r)>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
	tr[u]=tr[u<<1]*tr[u<<1|1];
}
void modify(int u,int l,int r,int pos,Mat val){
	if(l==r){tr[u]=val;return;}
	int mid=(l+r)>>1;
	if(pos<=mid)modify(u<<1,l,mid,pos,val);
	else modify(u<<1|1,mid+1,r,pos,val);
	tr[u]=tr[u<<1]*tr[u<<1|1];
}
Mat query(int u,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return tr[u];
	int mid=(l+r)>>1;
	if(qr<=mid)return query(u<<1,l,mid,ql,qr);
	if(ql>mid)return query(u<<1|1,mid+1,r,ql,qr);
	return query(u<<1,l,mid,ql,qr)*query(u<<1|1,mid+1,r,ql,qr);
}

// ====== 转移矩阵：唯一需要按题意改的地方 ======
// 这里是"第 i-1 根与第 i 根"的合法性矩阵，参数是两根的长度
// 当前按这个模型写的：第 x 根在坐标 x，向左倒覆盖 [x-a[x], x]，向右倒覆盖 [x, x+a[x]]，
// 边缘可以接触。由此推出：
//   (L,L) 合法 <=> a[i] == 1；(L,R) 恒合法；(R,R) 合法 <=> a[i-1] == 1；(R,L) 永不合法
// 如果原题的木棍间距不是 1，或"倒下的覆盖范围"不是这个定义，只需要改这个函数
Mat get_trans(int i){
	Mat M;
	M.v[0][0]=(a[i]==1);   // (L,L)
	M.v[0][1]=1;           // (L,R)
	M.v[1][0]=0;           // (R,L)
	M.v[1][1]=(a[i-1]==1); // (R,R)
	return M;
}
void rebuild_all(){//按当前 a[] 重建整棵线段树
	build(1,1,n);
	up(i,2,n)modify(1,1,n,i,get_trans(i));
}
int get_ans(){//当前方案数
	if(n==1)return 2;//只有一根：L 或 R
	Mat tot=query(1,1,n,2,n);
	int ans=0;
	up(i,0,1)up(j,0,1)ans=(ans+tot.v[i][j])%mod;
	return ans;
}
void solve(){
	int qq;
	cin>>n>>qq;
	up(i,1,n)cin>>a[i];
	rebuild_all();
	cout<<get_ans()<<'\n';
	while(qq--){
		int p,v;cin>>p>>v;
		a[p]=v;
		// 长度变了，只影响 p-1 与 p、p 与 p+1 两个相邻矩阵
		if(p>=2)modify(1,1,n,p,get_trans(p));
		if(p+1<=n)modify(1,1,n,p+1,get_trans(p+1));
		cout<<get_ans()<<'\n';
	}
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
//	cout << fixed << setprecision(10) << x << '\n';
	return 0;
}
/*
3 2
1 1 1
1 2
3 1
// 4
// 3
// 3

DDP 三步：
1. 每根木棍 2 个状态（L/R），相邻合法性写成 2x2 矩阵；
2. 整段方案数 = 初始向量 * 所有矩阵连乘，矩阵乘法有结合律，所以可以用线段树维护；
3. 单点修改 a[p] 只影响第 p、p+1 个矩阵，改两处后根节点就是答案，O(log n)。
*/
