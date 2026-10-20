#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
mt19937_64 gen(12345);
const int MAXN=105,mod=1e9+7;
int n,m,k;
// 普通矩阵乘法：C[i][j] = sum_k A[i][k]*B[k][j] (mod)
// 单位元是主对角线为 1、其余为 0 的矩阵
struct Mat{
	int sz,a[MAXN][MAXN];
	Mat(int s=0):sz(s){up(i,0,sz-1)up(j,0,sz-1)a[i][j]=0;}
	static Mat I(int s){Mat r(s);up(i,0,s-1)r.a[i][i]=1;return r;}
};
Mat operator*(const Mat&A,const Mat&B)
{
	Mat C(A.sz);
	up(i,0,A.sz-1)up(k,0,A.sz-1){
		if(!A.a[i][k])continue;//模意义下为 0 的项直接跳过
		up(j,0,B.sz-1)C.a[i][j]=(C.a[i][j]+A.a[i][k]*B.a[k][j])%mod;
	}
	return C;
}
Mat qpow(Mat A,int b)//A^b，复杂度 O(sz^3 log b)
{
	Mat res=Mat::I(A.sz);
	while(b){
		if(b&1)res=res*A;
		A=A*A,b>>=1;
	}
	return res;
}
// 例：斐波那契 f[1]=f[2]=1，求 f[b]。
// 转移矩阵 [[1,1],[1,0]] 的 b-1 次幂的左上角就是 f[b]
void solve(){
	int b;cin>>b;
	Mat A(2);
	A.a[0][0]=A.a[0][1]=A.a[1][0]=1,A.a[1][1]=0;
	cout<<qpow(A,b-1).a[0][0]<<'\n';
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
6
1
2
3
10
50
1000000000
// 1
// 1
// 2
// 55
// 586268941
// 21

MAXN 按题目矩阵规模改，常见不超过 105。
*/
