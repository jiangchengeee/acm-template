#include <bits/stdc++.h>
using namespace std;

// ==========================================
// 1. set 基础与查找
// ==========================================
void set_basics() {
	set<int> s;
	s.insert(3);
	s.insert(1);
	s.insert(4);
	s.insert(1); // set 自动去重，容器中只有 1, 3, 4
	
	// std::lower_bound(s.begin(), s.end(), x) 对 set 是 O(N)，
	// 应使用 set 的成员函数，复杂度 O(log N)。
	auto it1 = s.lower_bound(3); // 第一个 >= 3 的迭代器
	auto it2 = s.upper_bound(3); // 第一个 > 3 的迭代器
	
	// 找前驱和后继
	if (it1 != s.begin()) {
		auto pre = prev(it1); // 前驱（小于它的最大元素）
	}
	if (it1 != s.end()) {
		auto nxt = next(it1); // 后继，也可写 ++it1
	}
	
	// 遍历
	for (auto x : s) cout << x << " ";
}

// ==========================================
// 2. 自定义比较规则
// ==========================================
// 用于使 set 降序排列，或存储结构体。
struct Node {
	int l, r, val;
	// 按左端点升序，常用于 ODT
	bool operator<(const Node& other) const {
		return l < other.l;
	}
};

void set_custom() {
	// 内置类型改为降序排列
	set<int, greater<int>> s_desc; 
	
	// 结构体 set
	set<Node> odt;
	odt.insert({1, 5, 10});
}

// ==========================================
// 3. multiset 与删除陷阱
// ==========================================
void multiset_traps() {
	// multiset 允许重复元素，常用于动态维护最值或中位数
	multiset<int> ms = {1, 2, 2, 2, 3};
	
	// 陷阱 1：erase(x) 会删除所有等于 x 的元素
	ms.erase(2); 
	// 此时 ms 为 {1, 3}
	
	// 只删除一个元素应按迭代器删除
	multiset<int> ms2 = {1, 2, 2, 2, 3};
	auto it = ms2.find(2); 
	if (it != ms2.end()) {
		ms2.erase(it); // 只删除该迭代器指向的一个元素
	}
	// 此时 ms2 为 {1, 2, 2, 3}
	
	// 陷阱 2：count() 的复杂度为 O(log N + K)，K 为 x 的出现次数。
	// 元素大量重复时每次调用都可能超时。
	// 只判断存在性时改用 ms.find(x) != ms.end()。
}

// ==========================================
// 4. 用 set 维护区间（split 操作）
// ==========================================
// 利用 set 维护多个互不相交的区间。
set<Node> s; // Node 定义见上方
auto split(int pos) {
	// 找到第一个左端点 >= pos 的区间
	auto it = s.lower_bound({pos, 0, 0});
	// 已是某区间左端点则直接返回
	if (it != s.end() && it->l == pos) return it;
	
	// 否则 pos 一定在它前一个区间内部
	--it; 
	int l = it->l, r = it->r, v = it->val;
	s.erase(it); // 删除原区间
	s.insert({l, pos - 1, v}); // 插入左半部分
	return s.insert({pos, r, v}).first; // 插入右半部分并返回其迭代器
}
