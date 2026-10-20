#include <bits/stdc++.h>
using namespace std;

// ==========================================
// 1. 构造与查询
// ==========================================
void bitset_basics() {
	// 大小必须是编译期常量，不能用变量
	const int N = 1005; 
	bitset<N> bs1;             // 默认全 0
	bitset<N> bs2(13);         // 用十进制数初始化 (1101)
	bitset<N> bs3("101001");   // 用 01 字符串初始化
	
	// 状态统计
	int ones = bs3.count();    // O(N/64) 统计 1 的个数
	bool has_one = bs3.any();  // 是否至少有一个 1
	bool all_zero = bs3.none();// 是否全为 0
	bool all_one = bs3.all();  // 是否全为 1 (C++11)
}

// ==========================================
// 2. 修改与位运算
// ==========================================
void bitset_modifiers() {
	bitset<100> bs;
	
	// 单点修改 (O(1))
	bs.set(5);     // 将第 5 位设为 1 (最右边是第 0 位)
	bs.set(5, 0);  // 将第 5 位设为 0
	bs.reset(5);   // 等同于设为 0
	bs.flip(5);    // 翻转第 5 位
	
	// 整体修改 (O(N/64))
	bs.set();      // 全体设为 1
	bs.reset();    // 全体清零
	bs.flip();     // 全体取反
	
	// 位运算复杂度均为 O(N/64)，可当作集合运算使用
	bitset<100> a("1100"), b("1010");
	auto c = a & b; // 交集
	auto d = a | b; // 并集
	auto e = a ^ b; // 异或 (集合对称差)
	auto f = a << 3;// 整体左移
}

// ==========================================
// 3. 遍历所有 1 的位置 (GCC 专属)
// ==========================================
// 遍历复杂度与 1 的个数成正比；集合稀疏时优于逐位检查。

void bitset_iteration() {
	bitset<1000> bs("100100001000"); // 稀疏集合
	
	// 固定写法：
	// _Find_first() 返回第一个 1 的索引
	// _Find_next(i) 返回 i 之后的第一个 1 的索引
	// 找不到时返回 bs.size()
	for (int i = bs._Find_first(); i < bs.size(); i = bs._Find_next(i)) {
		cout << "在位置 " << i << " 发现了一个 1！" << endl;
	}
}

// ==========================================
// 4. 背包可行性：O(NV / 64)
// ==========================================
// n 个物品，体积 w[i]，求容量 V 内可凑出的体积；只判可行性，不求方案数。
void dp_bitset_knapsack() {
	vector<int> w = {2, 3, 7};
	int max_V = 10000;
	
	// dp[i] 为 1 表示体积 i 可以被凑出来
	bitset<10005> dp; 
	dp.set(0); // 体积 0 总是合法的
	
	for (int weight : w) {
		// 单次转移 O(V/64)：已凑出的体积加上 weight 后仍可凑出
		dp |= (dp << weight); 
	}
	
	if (dp[10]) cout << "能凑出体积 10" << endl;
}

// ==========================================
// 5. 传递闭包：O(V^3 / 64)
// ==========================================
// 有向图可达性。Floyd 为 O(V^3)，V = 2000 时超时，用 bitset 降至 O(V^3 / 64)。
void graph_transitive_closure() {
	const int V = 2005;
	bitset<V> reach[V]; // reach[i][j] 表示 i 能否到达 j
	
	// 假设图中存在边 (u, v)，则初始化 reach[u].set(v)
	
	// Floyd 算法
	for (int k = 0; k < V; k++) {
		for (int i = 0; i < V; i++) {
			// i 可达 k 时，k 能到达的点 i 也能到达
			if (reach[i][k]) {
				reach[i] |= reach[k]; // 单次合并 O(V/64)
			}
		}
	}
}
