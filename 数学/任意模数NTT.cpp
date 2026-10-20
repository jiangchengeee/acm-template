#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
// 任意模数 NTT：取三个 NTT 友好素数分别卷积，再用 CRT 拼回真实系数
// 三个素数乘积约 4.7e26；系数 < 1e9、n <= 1e6 时真实系数 < 1e24，能精确还原
const int P1=998244353, P2=1004535809, P3=469762049, G=3;
int MOD;                       // 目标模数，输入后设置
int ksm(int a,int b,int p){int r=1%p;for(;b;b>>=1,a=a*a%p)if(b&1)r=r*a%p;return r;}
void ntt(vector<int>&a,int p,bool inv)
{
	int n=a.size();
	for(int i=1,j=0;i<n;i++){
		int bit=n>>1;
		for(;j&bit;bit>>=1)j^=bit;
		j^=bit;
		if(i<j)swap(a[i],a[j]);
	}
	for(int len=2;len<=n;len<<=1){
		int w=ksm(G,(p-1)/len,p);
		if(inv)w=ksm(w,p-2,p);
		for(int i=0;i<n;i+=len){
			int wn=1;
			for(int k=0;k<len/2;k++){
				int u=a[i+k], v=a[i+k+len/2]*wn%p;
				a[i+k]=(u+v)%p;
				a[i+k+len/2]=(u-v+p)%p;
				wn=wn*w%p;
			}
		}
	}
}
vector<int> conv_mod(vector<int> a,vector<int> b,int p)//在模 p 下卷积
{
	int need=a.size()+b.size()-1, n=1;
	while(n<need)n<<=1;
	a.resize(n), b.resize(n);
	ntt(a,p,0), ntt(b,p,0);
	up(i,0,n-1)a[i]=a[i]*b[i]%p;
	ntt(a,p,1);
	int inv_n=ksm(n,p-2,p);
	up(i,0,need-1)a[i]=a[i]*inv_n%p;
	a.resize(need);
	return a;
}
int crt(int r1,int r2,int r3)//三个余数 -> 真实系数 mod MOD
{
	int t1=(r2-r1)%P2*ksm(P1%P2,P2-2,P2)%P2;
	t1=(t1+P2)%P2;
	int cur=(r1+P1%P3*(t1%P3))%P3;
	int t2=(r3-cur+P3)%P3*ksm(P1%P3*(P2%P3)%P3,P3-2,P3)%P3;
	int ans=r1%MOD;
	ans=(ans+P1%MOD*(t1%MOD))%MOD;
	ans=(ans+(P1%MOD)*(P2%MOD)%MOD*(t2%MOD))%MOD;
	return ans;
}
vector<int> mtt(vector<int> a,vector<int> b)//任意模数卷积
{
	if(a.empty()||b.empty())return {};
	auto c1=conv_mod(a,b,P1), c2=conv_mod(a,b,P2), c3=conv_mod(a,b,P3);
	int need=a.size()+b.size()-1;
	up(i,0,need-1)c1[i]=crt(c1[i],c2[i],c3[i]);
	return c1;
}
void solve(){
	int n,m;
	cin>>n>>m>>MOD;
	vector<int>a(n+1),b(m+1);
	up(i,0,n)cin>>a[i];
	up(i,0,m)cin>>b[i];
	auto c=mtt(a,b);
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
2 1 1000000007
1 2 1
1 1
// 1 3 3 1
*/
