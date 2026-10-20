#pragma GCC optimize("O3,unroll-loops")
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5; 
int n, m, cnt, root[N], a[N];
int ls[N << 5], rs[N << 5], w[N << 5];
vector<int> b;
int update(int lu, int l, int r, int x) {
    int u = ++cnt;
    ls[u] = ls[lu]; rs[u] = rs[lu]; w[u] = w[lu] + 1;
    if (l == r) return u;
    int mid = (l + r) >> 1;
    if (x <= mid) ls[u] = update(ls[lu], l, mid, x);
    else rs[u] = update(rs[lu], mid + 1, r, x);
    return u;
}
// 核心变化：前缀和相减，二分找第 K 小
int query(int u1, int u2, int l, int r, int k) {
    if (l == r) return l;
    int d = w[ls[u2]] - w[ls[u1]]; 
    int mid = (l + r) >> 1;
    if (k <= d) return query(ls[u1], ls[u2], l, mid, k); 
    else return query(rs[u1], rs[u2], mid + 1, r, k - d); 
}
void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b.push_back(a[i]);
    }
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    int max_val = b.size();
    for (int i = 1; i <= n; i++) {
        int x = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
        root[i] = update(root[i - 1], 1, max_val, x);
    }
    
    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;
        int ans_rk = query(root[l - 1], root[r], 1, max_val, k);
        cout << b[ans_rk - 1] << '\n'; 
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    solve();
    return 0;
}