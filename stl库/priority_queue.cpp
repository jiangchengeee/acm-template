#include <bits/stdc++.h>
using namespace std;

// ==========================================
// 1. 大根堆与小根堆
// ==========================================
void pq_basics() {
	// 1. 默认是大根堆，堆顶元素最大
	priority_queue<int> max_heap;
	max_heap.push(10);
	max_heap.push(30);
	max_heap.push(20);
	int top_max = max_heap.top(); // 30
	max_heap.pop();               // 弹出 30
	
	// 2. 小根堆需额外指定比较器，堆顶元素最小
	priority_queue<int, vector<int>, greater<int>> min_heap;
	min_heap.push(10);
	min_heap.push(30);
	min_heap.push(20);
	int top_min = min_heap.top(); // 10
}

// ==========================================
// 2. 存 pair
// ==========================================
void pq_pair() {
	// pair 默认先比较 first，再比较 second。
	// Dijkstra 中常用 first 存距离 dist、second 存节点编号 u。
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	
	pq.push({0, 1}); // 源点 1，距离 0
	pq.push({5, 2}); // 节点 2，距离 5
	
	auto [dist, u] = pq.top(); // C++17 结构化绑定
	pq.pop();
}

// ==========================================
// 3. 存结构体与比较规则
// ==========================================
struct Node {
	int u, dist;
	
	// 优先队列中若 a < b 为真，则 b 排在 a 前面，即更靠近堆顶。
	// 因此要让 dist 小的靠近堆顶，operator< 中需要写 dist > other.dist。
	bool operator<(const Node& other) const {
		// dist 小的靠近堆顶，故此处用大于号
		return dist > other.dist; 
	}
};

void pq_struct() {
	// 结构体内已重载 <，此处按默认方式声明即可，
	// 其行为等价于以 dist 为关键字的小根堆。
	priority_queue<Node> q;
	
	q.push({1, 10});
	q.push({2, 5});
	q.push({3, 20});
	
	// 堆顶为 dist 最小的元素，即 {2, 5}
	cout << q.top().u << " " << q.top().dist << endl; 
}

// ==========================================
// 4. 线性建堆
// ==========================================
void pq_linear_build() {
	vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
	
	// 做法一：逐个 push 入堆，复杂度 O(N log N)。
	priority_queue<int> q1;
	for(int x : v) q1.push(x);
	
	// 做法二：用迭代器区间构造，底层调用 std::make_heap，复杂度 O(N)。
	priority_queue<int> q2(v.begin(), v.end());
}
