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
// 区间第 k 小：前缀和相减，看左子树够不够
int query_kth(int u1, int u2, int l, int r, int k) {
    if (l == r) return l;
    int d = w[ls[u2]] - w[ls[u1]];//左子树里有多少个数
    int mid = (l + r) >> 1;
    if (k <= d) return query_kth(ls[u1], ls[u2], l, mid, k);
    else return query_kth(rs[u1], rs[u2], mid + 1, r, k - d);
}
// 区间第 k 大：和上面完全对称，改成先看右子树
int query_kth_max(int u1, int u2, int l, int r, int k) {
    if (l == r) return l;
    int d = w[rs[u2]] - w[rs[u1]];//右子树里有多少个数
    int mid = (l + r) >> 1;
    if (k <= d) return query_kth_max(rs[u1], rs[u2], mid + 1, r, k);
    else return query_kth_max(ls[u1], ls[u2], l, mid, k - d);
}
// 另一种写法：第 k 大 = 第 (区间长度 - k + 1) 小，直接复用小查询
// int kth_max_by_min(int u1,int u2,int l,int r,int k,int len){
//     return query_kth(u1,u2,l,r,len-k+1);
// }
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
        int rk_min = query_kth(root[l - 1], root[r], 1, max_val, k);
        int rk_max = query_kth_max(root[l - 1], root[r], 1, max_val, k);
        cout << b[rk_min - 1] << " " << b[rk_max - 1] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    solve();
    return 0;
}
/*
5 3
1 5 3 9 7
1 5 1
1 5 5
2 4 2
// 1 9
// 9 1
// 5 5

要点：
1. 离散化后建前缀主席树，区间 [l,r] 的计数 = root[r] - root[l-1]；
2. 第 k 小：看左子树的数量 d，k<=d 往左，否则 k-=d 往右；
3. 第 k 大：把"左"和"右"全部对调（看右子树）；
4. 等价关系：第 k 大 = 第 (len-k+1) 小，len=r-l+1，也可以直接复用小查询；
5. 复杂度：建树 O(n log n)，单次询问 O(log n)。
*/
