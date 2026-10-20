#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
// FFT：复数多项式乘法，O(n log n)
// 适用条件：系数非负且不太大（一般 |系数| < 1e5、长度 < 1e6 时结果 < 1e16，double 够用）
// 如果要精确大数或模意义下的结果，用 NTT / 任意模数 NTT
const double PI=acos(-1);
using cd=complex<double>;
void fft(vector<cd>&a,bool inv)//inv=true 时做逆变换（不除 n）
{
	int n=a.size();
	for(int i=1,j=0;i<n;i++){//位反转置换
		int bit=n>>1;
		for(;j&bit;bit>>=1)j^=bit;
		j^=bit;
		if(i<j)swap(a[i],a[j]);
	}
	for(int len=2;len<=n;len<<=1){
		double ang=2*PI/len*(inv?-1:1);
		cd w(cos(ang),sin(ang));//len 次单位根
		for(int i=0;i<n;i+=len){
			cd wn(1);
			for(int k=0;k<len/2;k++){
				cd u=a[i+k], v=a[i+k+len/2]*wn;
				a[i+k]=u+v, a[i+k+len/2]=u-v;
				wn*=w;
			}
		}
	}
}
vector<ll> conv(vector<ll> a,vector<ll> b)//多项式乘法，结果四舍五入回整数
{
	if(a.empty()||b.empty())return {};
	int need=a.size()+b.size()-1, n=1;
	while(n<need)n<<=1;
	vector<cd> fa(a.begin(),a.end()), fb(b.begin(),b.end());
	fa.resize(n), fb.resize(n);
	fft(fa,0), fft(fb,0);
	up(i,0,n-1)fa[i]*=fb[i];
	fft(fa,1);
	vector<ll> c(need);
	up(i,0,need-1)c[i]=llround(fa[i].real()/n);
	return c;
}
void solve(){
	int n,m;
	cin>>n>>m;
	vector<ll>a(n+1),b(m+1);
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
*/
