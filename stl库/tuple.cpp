#include <bits/stdc++.h>
using namespace std;

// ==========================================
// 1. 代替临时结构体，返回多个值
// ==========================================
// 需要同时返回是否有环、环的起点与环的长度时，可用 tuple 代替临时结构体。
tuple<bool, int, int> check_cycle() {
	// 逻辑省略...
	bool has_cycle = true;
	int start_node = 5;
	int length = 3;
	
	// 用大括号打包返回
	return {has_cycle, start_node, length};
}

void tuple_magic() {
	// ==========================================
	// 2. 结构化绑定 (C++17)
	// ==========================================
	// 无需 std::get<0>(t)，直接按顺序解构：
	auto [is_cyc, st, len] = check_cycle();
	
	if (is_cyc) {
		cout << "发现环！起点: " << st << ", 长度: " << len << "\n";
	}
	
	// ==========================================
	// 3. 字典序比较
	// ==========================================
	// Kruskal 需按边权排序，边为 (w, u, v)。
	// 存入 vector<tuple> 即可直接 sort，无需自定义结构体与比较函数。
	
	vector<tuple<int, int, int>> edges;
	edges.push_back({10, 1, 2}); // 边权 10，1 连 2
	edges.push_back({5, 2, 3});  // 边权 5，2 连 3
	edges.push_back({10, 2, 4}); // 边权 10，2 连 4
	
	// sort 按元素依次比较：先比边权，再比起点，最后比终点。
	sort(edges.begin(), edges.end());
	
	// 遍历排序后的边
	for (auto [w, u, v] : edges) {
		cout << "权值: " << w << " 起点: " << u << " 终点: " << v << "\n";
	}
}

// ==========================================
// 4. BFS 状态存储
// ==========================================
void tuple_bfs_example() {
	// 走迷宫时状态为 (x, y, keys, steps)，可用 queue<tuple> 存储。
	queue<tuple<int, int, int, int>> q;
	
	// 初始状态入队：x=0, y=0, keys=0, steps=0
	q.push({0, 0, 0, 0}); 
	
	while (!q.empty()) {
		// 取出全部状态
		auto [x, y, keys, steps] = q.front();
		q.pop();
		
		// 进行上下左右扩展...
	}
}
