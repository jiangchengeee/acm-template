#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
const int N=505,mod=1e9+7;
int ksm(int a,int b,int p){int r=1%p;for(;b;b>>=1,a=a*a%p)if(b&1)r=r*a%p;return r;}
// 高斯消元（模素数版）：解 n 元线性方程组
// a[i][j] 是第 i 个方程的系数，a[i][n] 是常数项
// 返回 0=唯一解（解在 a[i][n] 里）  1=多解  -1=无解
int gauss(int a[][N],int n){
	int r=0;
	up(c,0,n-1){
		int piv=-1;
		up(i,r,n-1)if(a[i][c]){piv=i;break;}
		if(piv==-1)continue;//这一列全是 0，跳过（秩不够）
		up(j,0,n)swap(a[r][j],a[piv][j]);
		int inv=ksm(a[r][c],mod-2,mod);
		up(j,0,n)a[r][j]=a[r][j]*inv%mod;
		up(i,0,n-1)if(i!=r&&a[i][c]){
			int t=a[i][c];
			up(j,0,n)a[i][j]=(a[i][j]-t*a[r][j]%mod+mod)%mod;
		}
		r++;
	}
	if(r<n){
		up(i,r,n-1)if(a[i][n])return -1;//秩 < n 但常数不全 0 -> 无解
		return 1;//秩 < n 且常数全 0 -> 多解
	}
	return 0;
}
void solve(){
	int n;
	int a[N][N];
	cin>>n;
	up(i,0,n-1)up(j,0,n)cin>>a[i][j];
	int st=gauss(a,n);
	if(st==-1)cout<<"NO SOLUTION\n";
	else if(st==1)cout<<"MULTIPLE\n";
	else up(i,0,n-1)cout<<a[i][n]<<" \n"[i==n-1];
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
//	cin >> T;
	while (T--){
		solve();
	}
//	system("x-www-browser https://ys.mihoyo.com/");
	return 0;
}
/*
2
1 1 3
1 -1 1
// 2 1

要点：
1. 逐列找主元、换到当前行、整行归一，再把其他行的这一列消成 0（列主元消去法）；
2. 秩 r < n：常数项出现非 0 -> 无解；否则多解（自由元随便取）；
3. 模素数才这么写；实数版把 ksm 换成直接除、判 0 用 eps；
4. 解异或方程组：沿用同一套，乘法是 &、加法是 ^、除法不用做。
*/
