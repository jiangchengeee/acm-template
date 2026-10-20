#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
mt19937_64 gen(12345);
const int MAXS=64,NEG=-(1ll<<60);
int n,m,k,R;
int a[8],c[8];
int dmg[1<<6],cost[1<<6];//每种"本轮使用集合"的伤害与基础花费
// 广义矩阵乘法（max-plus）：C[i][j] = max_k (A[i][k] + B[k][j])
// 单位元是主对角线为 0、其余为 -inf 的矩阵；-inf 表示该转移不存在
struct Mat{
	int sz,v[MAXS][MAXS];
	Mat(int s=0):sz(s){up(i,0,sz-1)up(j,0,sz-1)v[i][j]=NEG;}
	static Mat I(int s){Mat r(s);up(i,0,s-1)r.v[i][i]=0;return r;}
};
Mat operator*(const Mat&A,const Mat&B)
{
	Mat C(A.sz);
	up(i,0,A.sz-1)up(t,0,A.sz-1){
		if(A.v[i][t]==NEG)continue;//不存在的转移直接跳过
		up(j,0,B.sz-1){
			if(B.v[t][j]==NEG)continue;
			C.v[i][j]=max(C.v[i][j],A.v[i][t]+B.v[t][j]);
		}
	}
	return C;
}
Mat qpow(Mat A,int b)
{
	Mat res=Mat::I(A.sz);
	while(b){
		if(b&1)res=res*A;
		A=A*A,b>>=1;
	}
	return res;
}
// Blood Memories：n 个角色，每轮 m 点能量，角色 i 技能伤害 a[i]、基础花费 c[i]。
// 上一轮用过技能的角色，本轮花费变成 c[i]+k（连续使用不再叠加）；没用过就恢复成 c[i]。
// 每轮每人最多用一次、总花费不超过 m，求 R 轮最大总伤害。
// 状态取"上一轮用过技能的角色集合"（n<=6，共 2^n 种），转移只与状态有关：
//     M[P][T] = 本轮用集合 T 能拿到的伤害（当 T 的花费不超过 m 时），否则 -inf
// 于是 R 轮就是一个 max-plus 矩阵幂：答案 = max_T (M^R)[0][T]（初始状态是空集）
void solve(){
	cin>>n>>m>>k>>R;
	up(i,0,n-1)cin>>a[i]>>c[i];
	int S=1<<n;
	up(T,0,S-1){
		int d=0,cc=0;
		up(i,0,n-1)if(T>>i&1)d+=a[i],cc+=c[i];
		dmg[T]=d,cost[T]=cc;
	}
	Mat M(S);
	up(P,0,S-1)up(T,0,S-1){
		int need=cost[T]+k*__builtin_popcountll(T&P);//P 里用过的角色要多花 k
		if(need<=m)M.v[P][T]=dmg[T];
	}
	Mat pw=qpow(M,R);
	int ans=0;
	up(T,0,S-1)ans=max(ans,pw.v[0][T]);
	cout<<ans<<'\n';
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
//    system("x-www-browser https://ys.mihoyo.com/");
    return 0;
}
/*
3
3 7 1 5
59 3
13 2
81 4
5 14 2 9
66 8
20 2
25 4
39 6
57 7
4 13 7 16
18 2
13 5
33 4
7 1
// 490
// 939
// 741

矩阵规模 2^n <= 64，单组复杂度 O(2^{3n} log R)。
*/
