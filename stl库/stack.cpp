#include <bits/stdc++.h>
using namespace std;

// ==========================================
// 1. stack 基础用法
// ==========================================
void stack_basics() {
	stack<int> st;
	st.push(1); // 入栈
	st.push(2);
	
	int top_val = st.top(); // 获取栈顶元素 (2)
	st.pop();               // 弹出栈顶 (无返回值)
	
	bool is_empty = st.empty(); // 判断是否为空
	
	// std::stack 不支持访问栈底元素，也不支持遍历。
}

// ==========================================
// 2. 数组模拟栈
// ==========================================
void array_stack() {
	const int N = 100005;
	int stk[N], top_idx = 0; // top_idx 表示栈中元素个数
	
	// 入栈 (push)
	stk[++top_idx] = 10;
	stk[++top_idx] = 20;
	
	// 访问栈顶 (top)
	int val = stk[top_idx]; 
	
	// 出栈 (pop)
	top_idx--; 
	
	// 判断为空 (empty)
	bool empty = (top_idx == 0);
	
	// 数组模拟栈可直接从栈底到栈顶遍历
	for (int i = 1; i <= top_idx; i++) {
		cout << stk[i] << " ";
	}
}

// 也可用 vector 模拟栈：push_back() 入栈，pop_back() 出栈，back() 取栈顶。

// ==========================================
// 3. 单调栈
// ==========================================
// 求每个元素左侧 / 右侧第一个比它大或小的元素，复杂度 O(N)，每个元素至多进出栈一次。
// 经典题目：最大矩形面积（LeetCode 84）、视野总和。

void monotonic_stack_example() {
	vector<int> a = {2, 1, 5, 6, 2, 3};
	int n = a.size();
	
	// ans[i] 为 i 右侧第一个比 a[i] 小的元素下标，
	// 不存在这样的元素时保持初值 n。
	vector<int> ans(n, n); 
	
	// 栈中存下标而非值
	stack<int> st; 
	
	for (int i = 0; i < n; i++) {
		// 维护单调递增栈：a[i] 小于栈顶元素时，
		// 栈顶元素右侧第一个比它小的元素即为 a[i]。
		while (!st.empty() && a[st.top()] > a[i]) {
			int top_idx = st.top();
			ans[top_idx] = i; // 记录答案
			st.pop();         // 弹出栈顶
		}
		// 新元素下标入栈
		st.push(i);
	}
	
	// 遍历结束后栈中剩余元素右侧没有更小的数，ans 保持默认值 n。
}
