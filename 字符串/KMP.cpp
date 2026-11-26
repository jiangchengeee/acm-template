#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
const int N=1e6+5;
int nxt[N];//nxt[i] = p[0..i] 的最长公共前后缀长度
void get_next(string &p){
	int m=p.size();
	nxt[0]=0;
	for(int i=1,j=0;i<m;i++){
		while(j&&p[i]!=p[j])j=nxt[j-1];
		if(p[i]==p[j])j++;
		nxt[i]=j;
	}
}
void kmp(string &s,string &p){//输出 p 在 s 中所有出现位置（1-based 起点）
	get_next(p);
	int n=s.size(),m=p.size();
	for(int i=0,j=0;i<n;i++){
		while(j&&s[i]!=p[j])j=nxt[j-1];
		if(s[i]==p[j])j++;
		if(j==m){
			cout<<i-m+2<<'\n';
			j=nxt[j-1];//继续找下一次
		}
	}
}
int min_period(string &s){//最小循环节长度：n - nxt[n-1]
	get_next(s);
	int n=s.size();
	return n-nxt[n-1];
}
void solve(){
	string s,p;
	cin>>s>>p;
	kmp(s,p);
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
abababab
abab
// 1
// 3
// 5

要点：
1. nxt[i] 是"前缀 p[0..i] 的最长公共真前后缀长度"；
2. 失配时 j = nxt[j-1] 继续跳，均摊 O(n+m)；
3. 最小循环节 = n - nxt[n-1]（且能被整除时才是完整的循环节）。
*/
