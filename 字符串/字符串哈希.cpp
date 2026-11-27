#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
const int N=1e6+5;
typedef unsigned long long ull;
const ull B=131;//基数，比赛时改成随机值可以防被卡
ull h[N],pw[N];
void init_hash(string &s){//s 下标 0 起，哈希下标 1 起
	int n=s.size();
	pw[0]=1;
	up(i,1,n)pw[i]=pw[i-1]*B;
	h[0]=0;
	up(i,1,n)h[i]=h[i-1]*B+s[i-1];
}
ull get(int l,int r){//子串 s[l-1..r-1] 的哈希（1-based 闭区间）
	return h[r]-h[l-1]*pw[r-l+1];
}
bool same(int l1,int r1,int l2,int r2){
	if(r1-l1!=r2-l2)return 0;
	return get(l1,r1)==get(l2,r2);
}
void solve(){
	string s;
	cin>>s;
	init_hash(s);
	int q;cin>>q;
	while(q--){
		int l1,r1,l2,r2;
		cin>>l1>>r1>>l2>>r2;
		cout<<(same(l1,r1,l2,r2)?"Yes":"No")<<'\n';
	}
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
abacaba
3
1 3 5 7
1 2 4 5
1 7 1 7
// Yes
// No
// Yes

要点：
1. 自然溢出（unsigned long long），常数小、够快；
2. 想稳一点用双模：mod1=1e9+7, mod2=1e9+9，两套哈希都相等才算相等；
3. 基数用随机的奇数（时间种子），防止被出题人卡；
4. 求 LCP（最长公共前缀）可以二分 + 哈希，O(log n)。
*/
