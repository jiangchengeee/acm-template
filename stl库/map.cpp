#include <bits/stdc++.h>
using namespace std;

// ==========================================
// 1. map 基础
// ==========================================
void map_basics() {
	map<string, int> mp;
	
	// 基础插入
	mp["apple"] = 5; 
	mp.insert({"banana", 3});
	
	// [] 访问不存在的键会自动插入默认值，所以不能用 mp["x"] > 0 判断存在性；
	// 循环中反复访问不存在的键会使 map 不断增长，可能 MLE 或 TLE。
	// 判断存在性应当用 count 或 find：
	
	if (mp.count("orange")) { // 返回 0 或 1
		// 存在
	}
	if (mp.find("orange") != mp.end()) {
		// 存在
	}
}

// ==========================================
// 2. 有序性与二分
// ==========================================
void map_advanced() {
	map<int, string> mp;
	mp[10] = "A";
	mp[20] = "B";
	mp[30] = "C";
	
	// map 按键有序，可直接二分
	// 第一个键 >= 25 的元素
	auto it = mp.lower_bound(25); 
	if (it != mp.end()) {
		cout << it->first << " " << it->second << endl; // 输出 30 C
	}
	
	// 按键由大到小逆序遍历
	for (auto it = mp.rbegin(); it != mp.rend(); ++it) {
		cout << it->first << " " << it->second << endl;
	}
	
	// 按键降序：传入 greater<int>
	map<int, string, greater<int>> mp_desc;
}

// ==========================================
// 3. unordered_map 与 pair 哈希
// ==========================================
// 标准库未为 pair 提供哈希函数，unordered_map<pair<int, int>, int> 无法通过编译，
// 需自行提供哈希函数。

struct pair_hash {
	template <class T1, class T2>
	size_t operator () (const pair<T1, T2>& p) const {
		auto h1 = hash<T1>{}(p.first);
		auto h2 = hash<T2>{}(p.second);
		// 组合两个哈希值，降低冲突概率
		return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
	}
};

void unordered_map_usage() {
	// 基础用法
	unordered_map<int, int> ump;
	ump[1] = 100;
	
	// 使用自定义 pair_hash
	// 常用于二维坐标的点权与有向边的权值
	unordered_map<pair<int, int>, int, pair_hash> edge_weight;
	
	edge_weight[{1, 2}] = 50; // 边 (1, 2) 的权值为 50
	
// 原生 std::unordered_map<int, int> 的哈希函数可被构造数据卡到单次操作 O(N)。
// 解决方式：使用 PBDS 的 gp_hash_table，或为 unordered_map 指定自定义哈希：
	// unordered_map<long long, int, custom_hash> safe_ump;
}
