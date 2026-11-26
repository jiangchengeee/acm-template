#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
const int N=1e6+5;
int tr[N][26],fail[N],cnt[N],tot;
void insert(string &s){//建 Trie
	int u=0;
	for(char c:s){
		int v=c-'a';
		if(!tr[u][v])tr[u][v]=++tot;
		u=tr[u][v];
	}
	cnt[u]++;//这个结点代表一个模式串结尾
}
void build(){//BFS 求 fail 指针
	queue<int>q;
	up(i,0,25)if(tr[0][i])q.push(tr[0][i]);
	while(!q.empty()){
		int u=q.front();q.pop();
		up(i,0,25){
			int v=tr[u][i];
			if(v){
				fail[v]=tr[fail[u]][i];//失配后跳到的位置
				q.push(v);
			}else tr[u][i]=tr[fail[u]][i];//路径压缩，直接接上 fail 的儿子
		}
	}
}
int query(string &s){//返回模式串在 s 中出现次数之和
	int u=0,res=0;
	for(char c:s){
		u=tr[u][c-'a'];
		for(int v=u;v;v=fail[v]){//沿 fail 链把结尾标记收掉（-1 表示已统计过，跳过但不能停）
			if(cnt[v]!=-1)res+=cnt[v],cnt[v]=-1;
		}
	}
	return res;
}
void solve(){
	int n;
	cin>>n;
	up(i,1,n){
		string s;cin>>s;
		insert(s);
	}
	build();
	string t;cin>>t;
	cout<<query(t)<<'\n';
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
3
a
ab
bab
abab
// 3   （a 出现 2 次、ab 出现 2 次、bab 出现 1 次？按"每个模式串只统计一次"输出 3）

要点：
1. insert 建 Trie 并在结尾打标记，build 用 BFS 求 fail；
2. tr[u][i] = tr[fail[u]][i] 这步把转移补全，查的时候不用再跳 fail；
3. 统计"出现次数"要沿 fail 链累加；要"每个模式串只算一次"就把访问过的 cnt 置 -1；
4. 需要每个模式串各出现几次时，用 fail 树上的子树和（建完 fail 后 dfs 累加）。
*/
