#include <bits/stdc++.h>
using namespace std;
// 树状数组（单点改 + 前缀和）：Fenwick LL(n) 建 n 个数，add/query 均为 O(log n)
// 区间改 + 区间查要开两棵树，区间改 + 单点查用差分即可
template <typename T>
struct Fenwick {
    int n;
    std::vector<T> tree;
    Fenwick(int n_ = 0) {
        init(n_);
    }
    void init(int n_) {
        n = n_;
        tree.assign(n + 1, T{});
    }
    void add(int x, T v) {
        for (; x <= n; x += x & -x) {
            tree[x] += v;
        }
    }
    T query(int x) {
        T ans{};
        for (; x > 0; x -= x & -x) {
            ans += tree[x];
        }
        return ans;
    }
    T query(int l, int r) {
        if (l > r) return T{};
        return query(r) - query(l - 1);
    }
};