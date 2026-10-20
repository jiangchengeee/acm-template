#pragma GCC optimize("O3,unroll-loops")
#include <iostream>
using namespace std;
const int N = 2e5 + 5; 
int n, q, cnt, root[N];
int ls[N * 40], rs[N * 40], min_pos[N * 40]; 
int update(int pre, int l, int r, int x, int pos) {
    int u = ++cnt;
    ls[u] = ls[pre]; rs[u] = rs[pre]; 
    if (l == r) {
        min_pos[u] = pos;
        return u;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) ls[u] = update(ls[pre], l, mid, x, pos);
    else rs[u] = update(rs[pre], mid + 1, r, x, pos);
    min_pos[u] = min(min_pos[ls[u]], min_pos[rs[u]]);
    return u;
}
int query(int u, int l, int r, int limit_L) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (min_pos[ls[u]] < limit_L) return query(ls[u], l, mid, limit_L);
    else return query(rs[u], mid + 1, r, limit_L);
}
void solve() {
    cin >> n >> q;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        if (x > n + 1) {
            root[i] = root[i - 1];
        } else {
            root[i] = update(root[i - 1], 0, n + 1, x, i);
        }
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << query(root[r], 0, n + 1, l) << '\n';
    }
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}