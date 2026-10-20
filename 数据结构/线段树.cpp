#include <bits/stdc++.h>
using namespace std;
long long a[100005];
template <typename T>
struct SegTree {
    struct Node {
        T w, tag;
    };
    int n;
    std::vector<Node> t;
    SegTree(int n_ = 0) { init(n_); }
    SegTree(const std::vector<T>& a) { init(a); }
    void init(int n_) {
        n = n_;
        t.assign(4 * n + 1, {0, 0});
    }
    void init(const std::vector<T>& a) {
        n = a.size() - 1; // 默认 a 是 1-indexed
        t.assign(4 * n + 1, {0, 0});
        auto build = [&](auto &&self, int u, int l, int r) -> void {
            if (l == r) { t[u].w = a[l]; return; }
            int mid = (l + r) >> 1;
            self(self, u << 1, l, mid);
            self(self, u << 1 | 1, mid + 1, r);
            pushup(u);
        };
        build(build, 1, 1, n);
    }
    inline void pushup(int u) {
        t[u].w = t[u << 1].w + t[u << 1 | 1].w;
    }

    inline void maketag(int u, int len, T x) {
        t[u].tag += x;
        t[u].w += len * x;
    }
    inline void pushdown(int u, int l, int r) {
        if (t[u].tag) {
            int mid = (l + r) >> 1;
            maketag(u << 1, mid - l + 1, t[u].tag);
            maketag(u << 1 | 1, r - mid, t[u].tag);
            t[u].tag = 0;
        }
    }
    void update(int u, int l, int r, int ql, int qr, T x) {
        if (ql <= l && r <= qr) {
            maketag(u, r - l + 1, x);
            return;
        }
        pushdown(u, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(u << 1, l, mid, ql, qr, x);
        if (qr > mid) update(u << 1 | 1, mid + 1, r, ql, qr, x);
        pushup(u);
    }

    T query(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return t[u].w;
        pushdown(u, l, r);
        int mid = (l + r) >> 1;
        T ans = 0;
        if (ql <= mid) ans += query(u << 1, l, mid, ql, qr);
        if (qr > mid) ans += query(u << 1 | 1, mid + 1, r, ql, qr);
        return ans;
    }
    void update(int ql, int qr, T x) { update(1, 1, n, ql, qr, x); }
    T query(int ql, int qr) { return query(1, 1, n, ql, qr); }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    SegTree<long long> tr(a); 
    while (m--) {
        int op, x, y;
        long long k;
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> k;
            tr.update(x, y, k);
        } else {
            cin >> x >> y;
            cout << tr.query(x, y) << '\n';
        }
    }
    return 0;
}
