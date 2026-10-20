#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;

template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void test_ordered_set() {
    ordered_set<int> st; // 元素类型可换成 ll 等
    st.insert(10);
    st.insert(30);
    st.insert(30); // 自动去重
    
    int rank = st.order_of_key(30); // 严格小于 30 的个数，返回 1
    int val = *st.find_by_order(1); // 排名第 2 的数，下标从 0 开始，返回 30
}

template <typename T>
struct ordered_multiset {
    ordered_set<pair<T, int>> tr; 
    int timer = 0; // 区分相同元素的时间戳
    
    // 插入 x
    void insert(T x) { 
        tr.insert({x, ++timer}); 
    }
    
    // 删除一个值为 x 的元素
    void erase(T x) {
        // timer 从 1 开始，{x, 0} 可定位到值恰为 x 的第一个元素
        auto it = tr.lower_bound({x, 0});
        if (it != tr.end() && it->first == x) {
            tr.erase(it);
        }
    }
    
    // 严格小于 x 的元素个数
    int rank(T x) { 
        return tr.order_of_key({x, 0}); 
    }
    
    // 第 k 小的数，k 从 0 开始
    T k_th(int k) { 
        return tr.find_by_order(k)->first; 
    }
    
    // 值 <= x 的元素个数
    int count_less_equal(T x) {
        // 取 timer 的极大值，覆盖所有值为 x 的元素
        return tr.order_of_key({x, 2e9}); 
    }
    
    int size() { return tr.size(); }
    void clear() { tr.clear(); timer = 0; }
};

void test_ordered_multiset() {
    ordered_multiset<ll> ms; // 元素类型为 ll
    ms.insert(30ll);
    ms.insert(30ll);
    ms.insert(10ll);
    
    int r = ms.rank(30ll);       // 只有 10 严格小于 30，返回 1
    ll val = ms.k_th(1);         // 排名第 2 的元素，返回 30
    int cnt = ms.count_less_equal(30ll); // 三个数 <= 30，返回 3
}