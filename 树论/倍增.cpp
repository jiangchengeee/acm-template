#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int LOG = 20; // log2(100005) 向上取整，通常 20 足够应付 5e5 的数据
vector<vector<int>> f;
int depth[MAXN];
int fa[MAXN][LOG];
void dfs(int u, int parent) {
	depth[u] = depth[parent] + 1; 
	fa[u][0] = parent;           
	
	for (int k = 1; k < LOG; k++) {
		fa[u][k] = fa[fa[u][k - 1]][k - 1];
	}
	for (int v : f[u]) {
		if (v != parent) {
			dfs(v, u);
		}
	}
}
int get_lca(int u, int v) {
	if (depth[u] < depth[v]) {
		swap(u, v);
	}
	for (int k = LOG - 1; k >= 0; k--) {
		if (depth[fa[u][k]] >= depth[v]) {
			u = fa[u][k];
		}
	}
	if (u == v) return u;
	for (int k = LOG - 1; k >= 0; k--) {
		if (fa[u][k] != fa[v][k]) {
			u = fa[u][k];
			v = fa[v][k];
		}
	}
	return fa[u][0];
}
void solve() {
	int n, m, root;
	cin >> n >> m >> root;
	f.assign(n + 1, vector<int>());
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		f[u].push_back(v);
		f[v].push_back(u);
	}
	depth[0] = 0; 
	dfs(root, 0);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		cout << get_lca(u, v) << "\n";
	}
}
