#include <bits/stdc++.h>
using namespace std;

// ==========================================
// 1. queue 基础用法
// ==========================================
void queue_basics() {
	queue<int> q;
	q.push(1); // 入队
	q.push(2);
	
	int head = q.front(); // 队头元素 (1)
	q.pop();              // 弹出队头，无返回值
	
	// std::queue 没有 clear()，多组数据下直接调用会编译报错。
	
	// 方式一：赋值为空队列
	q = queue<int>(); 
	
	// 方式二：与空队列 swap
	queue<int>().swap(q);
	
	// 方式三：while(!q.empty()) q.pop(); 常数较大
}

// ==========================================
// 2. deque 与 0-1 BFS
// ==========================================
// deque 支持在头部和尾部以 O(1) 插入和删除，并支持随机访问。
void deque_01_bfs() {
	deque<int> dq;
	
	// 基础操作：头尾均可进出
	dq.push_back(1);
	dq.push_front(2);
	dq.pop_back();
	dq.pop_front();
	
	// 边权只有 0 和 1 时可用 0-1 BFS 求最短路，
	// 复杂度 O(V + E)，优于 Dijkstra 的 O(E log V)。
	
	// 伪代码：核心逻辑
	/*
	dq.push_front(起点);
	while (!dq.empty()) {
	int u = dq.front(); dq.pop_front();
	for (auto edge : graph[u]) {
	int v = edge.to, w = edge.weight; // w 只能是 0 或 1
	if (dist[u] + w < dist[v]) {
	dist[v] = dist[u] + w;
	// 边权为 0 入队头，边权为 1 入队尾
	if (w == 0) dq.push_front(v);
	else dq.push_back(v);
	}
	}
	}
	*/
}

// ==========================================
// 3. 单调队列
// ==========================================
// 用于求滑动窗口内的最大值 / 最小值，复杂度 O(N)，每个元素至多进出队列一次。
// 队列中存下标；进队前弹出队尾所有不大于 a[i] 的元素，队头即当前窗口的最值。

void monotonic_queue_example() {
	vector<int> a = {1, 3, -1, -3, 5, 3, 6, 7}; // 原数组
	int k = 3; // 滑动窗口大小为 3
	int n = a.size();
	
	deque<int> q; // 存储数组下标
	vector<int> max_res; // 存储每个窗口的最大值
	
	for (int i = 0; i < n; i++) {
		// 步骤 1：弹出已滑出窗口 [i-k+1, i] 的队头
		// q.front() <= i - k 时该下标已过期
		if (!q.empty() && q.front() <= i - k) {
			q.pop_front();
		}
		
		// 步骤 2：维护单调递减性。a[i] 入队更晚且不小于队尾元素，
		// 故队尾元素不可能再成为窗口最大值，可直接弹出。
		while (!q.empty() && a[q.back()] <= a[i]) {
			q.pop_back();
		}
		
		// 步骤 3：新元素下标入队
		q.push_back(i);
		
		// 步骤 4：窗口形成后记录答案，队头即最大值的下标
		if (i >= k - 1) {
			max_res.push_back(a[q.front()]);
		}
	}
	
	// 输出 max_res 即每个窗口的最大值
}
