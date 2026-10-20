#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
// NTT：模 998244353 的多项式乘法，O(n log n)
// 998244353 = 119*2^23+1，原根 3，所以长度必须是 2 的幂且不超过 2^23
const int MOD=998244353, G=3;
int ksm(int a,int b,int p){int r=1%p;for(;b;b>>=1,a=a*a%p)if(b&1)r=r*a%p;return r;}
void ntt(vector<int>&a,bool inv)//inv=true 时做逆变换（不除 n）
{
	int n=a.size();
	for(int i=1,j=0;i<n;i++){//位反转置换
		int bit=n>>1;
		for(;j&bit;bit>>=1)j^=bit;
		j^=bit;
		if(i<j)swap(a[i],a[j]);
	}
	for(int len=2;len<=n;len<<=1){
		int w=ksm(G,(MOD-1)/len,MOD);//len 次单位根
		if(inv)w=ksm(w,MOD-2,MOD);
		for(int i=0;i<n;i+=len){
			int wn=1;
			for(int k=0;k<len/2;k++){
				int u=a[i+k], v=a[i+k+len/2]*wn%MOD;
				a[i+k]=(u+v)%MOD;
				a[i+k+len/2]=(u-v+MOD)%MOD;
				wn=wn*w%MOD;
			}
		}
	}
}
vector<int> conv(vector<int> a,vector<int> b)//多项式乘法
{
	if(a.empty()||b.empty())return {};
	int need=a.size()+b.size()-1, n=1;
	while(n<need)n<<=1;
	a.resize(n), b.resize(n);
	ntt(a,0), ntt(b,0);
	up(i,0,n-1)a[i]=a[i]*b[i]%MOD;
	ntt(a,1);
	int inv_n=ksm(n,MOD-2,MOD);
	up(i,0,need-1)a[i]=a[i]*inv_n%MOD;
	a.resize(need);
	return a;
}
void solve(){
	int n,m;
	cin>>n>>m;
	vector<int>a(n+1),b(m+1);
	up(i,0,n)cin>>a[i];
	up(i,0,m)cin>>b[i];
	auto c=conv(a,b);
	up(i,0,n+m)cout<<c[i]<<" \n"[i==n+m];
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
	return 0;
}
/*
2 1
1 2 1
1 1
// 1 3 3 1

长度是 2 的幂、且不超过 2^23 = 8388608 才能直接用。
*/
