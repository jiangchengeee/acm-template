#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
const int N=1e6+5;
int p[N*2];//p[i] = 以变换后位置 i 为中心的回文半径
// 返回最长回文子串长度，同时 p[] 里存下每个中心的信息
int manacher(string &s){
	string t="#";
	for(char c:s)t+=c,t+='#';
	int n=t.size(),ans=0,mx=0,mid=0;
	up(i,0,n-1){
		p[i]=(i<mx)?min(mx-i+1,p[2*mid-i]):1;//省去一半的暴力扩展
		while(i-p[i]>=0&&i+p[i]<n&&t[i-p[i]]==t[i+p[i]])p[i]++;
		if(i+p[i]-1>mx)mid=i,mx=i+p[i]-1;
		ans=max(ans,p[i]-1);
	}
	return ans;
}
// 如果要还原具体子串：以变换后位置 i 为中心，回文长度 p[i]-1，
// 原串起点 = (i-(p[i]-1))/2，长度 = p[i]-1
void solve(){
	string s;
	cin>>s;
	cout<<manacher(s)<<'\n';
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
// 7

要点：
1. 先插入分隔符把奇偶回文统一成奇回文；
2. mx 是已探明的最右回文边界，能直接抄左边对称位置的答案；
3. p[i]-1 就是原串里以 i 为中心的回文长度。
*/
