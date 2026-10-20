#pragma GCC optimize("O2")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // 包含所有容器（哈希表、树、堆）
#include <ext/pb_ds/tree_policy.hpp>     // 包含树的相关策略（用于实现平衡树）
#include <ext/pb_ds/hash_policy.hpp>     // 包含哈希表的相关策略
//#include <ext/pb_ds/priority_queue.hpp>  // 包含优先级队列（堆）
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define sm int,vector<int>,greater<int>
#define int long long
mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
const int N=1e6+5,mod=998244353,inf=1e9+7;;
int n,m,q,k;
int a[N],b[N],c[N],d[N];
int gcd(int x,int y)
{
	if(y==0)return x;
	return gcd(y,x%y);
}
int ksm(int a,int n,int p)
{
	if(n<0)return 0;
	int res=1;
	while(n)
	{
		if(n&1)res=res*a%p;
		n>>=1;
		a=a*a%p;
	}
	return res;
}
void solve(){
	
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
//	system("x-www-browser https://ys.mihoyo.com/");
//	cout << fixed << setprecision(10) << x << '\n';
	return 0;
}
/*
1
3411 4134 32 23


*/
