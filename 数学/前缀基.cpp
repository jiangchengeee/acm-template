#include <iostream>
#include <vector>

using ll = long long;
using namespace std;
const int MOD = 998244353;

ll qpow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

/**
 * 线性批量求逆元 (前缀积法)
 * 传入需要求逆元的数组 a (1-indexed)，将结果存入 inv_a (1-indexed)
 * 时间复杂度: O(n + log(MOD))
 */
void linear_inv(const std::vector<ll>& a, std::vector<ll>& inv_a) {
    int n = a.size() - 1;
    if (n <= 0) return;
    std::vector<ll> pre(n + 1, 1), inv_pre(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] * a[i] % MOD;
    }
    inv_pre[n] = qpow(pre[n], MOD - 2);
    for (int i = n; i >= 1; i--) {
        inv_pre[i - 1] = inv_pre[i] * a[i] % MOD;
    }
    for (int i = 1; i <= n; i++) {
        inv_a[i] = inv_pre[i] * pre[i - 1] % MOD;
    }
}