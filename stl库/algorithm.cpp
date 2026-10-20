#include <bits/stdc++.h>
using namespace std;

// ==========================================
// 1. 排序与极值
// ==========================================
void algo_sort_extrema() {
	vector<int> a = {5, 1, 4, 2, 3, 4};
	
	// 1. 稳定排序
	// 关键字相等的元素保持原有相对顺序。
	stable_sort(a.begin(), a.end()); 
	
	// 2. 线性时间求第 K 小 (O(N))
	// 用于求中位数或前 K 小，不要求整体有序。
	// 执行后 a[2] 为第 3 小的数，左侧元素均不大于它，右侧元素均不小于它。
	nth_element(a.begin(), a.begin() + 2, a.end()); 
	
	// 3. 一次遍历同时求最小值与最大值
	auto [min_it, max_it] = minmax_element(a.begin(), a.end());
	cout << "Min: " << *min_it << ", Max: " << *max_it << endl;
}

// ==========================================
// 2. 全排列与序列变换
// ==========================================
void algo_transform() {
	vector<int> p = {1, 2, 3};
	
	// 1. 下一个全排列 (适用于 N 较小的枚举)
	// 使用前数组必须升序。
	do {
		// 依次产生: 123, 132, 213, 231, 312, 321
	} while (next_permutation(p.begin(), p.end()));
	
	// 2. 区间循环移位
	// 使 middle 成为新的首元素，[first, middle) 移到末尾，O(N)。
	vector<int> v = {1, 2, 3, 4, 5};
	// 以 v.begin() + 2 (即数字 3) 为新的首元素
	rotate(v.begin(), v.begin() + 2, v.end()); 
	// 结果 v = {3, 4, 5, 1, 2}
}

// ==========================================
// 3. 有序数组的集合操作
// ==========================================
// 求两个已升序数组的交集、并集、差集，复杂度 O(N + M)；
// 用 std::set 实现需要 O(N log N)。
void algo_set_ops() {
	vector<int> v1 = {1, 2, 4, 5, 7};
	vector<int> v2 = {2, 3, 5, 6};
	vector<int> res(10); // 需提前分配足够大的空间
	
	// 求交集，返回结果区间的尾后迭代器
	auto it = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), res.begin());
	// 删除多余空间
	res.resize(it - res.begin()); 
	// 此时 res = {2, 5}
	
	// 其他集合操作：
	// set_union (并集: 1, 2, 3, 4, 5, 6, 7)
	// set_difference (差集 v1 - v2: 1, 4, 7)
}

// ==========================================
// 4. numeric 常用函数
// ==========================================
void numeric_magic() {
	vector<int> a(5);
	
	// 1. iota：从初值开始递增填充
	// 常用于并查集初始化 fa[i] = i。
	iota(a.begin(), a.end(), 1); 
	// 结果 a = {1, 2, 3, 4, 5}
	
	// 2. accumulate：区间求和
	// 第三个参数的类型即累加使用的类型。
	vector<int> big_nums = {1000000000, 1000000000, 1000000000};
	
	// 按 int 累加，会整型溢出
	long long sum_wrong = accumulate(big_nums.begin(), big_nums.end(), 0); 
	
	// 写成 0LL，按 long long 累加
	long long sum_right = accumulate(big_nums.begin(), big_nums.end(), 0LL);
	
	// 3. gcd / lcm (C++17 起可用)
	int g = std::gcd(12, 18); // 返回 6
	int l = std::lcm(12, 18); // 返回 36
}

// ==========================================
// 5. 填充与离散化
// ==========================================
void fill_and_discretize() {
	// 1. fill：按值填充
	// memset 按字节填充，只能填 0、-1、0x3f 等；填 100 这类值须用 fill。
	vector<int> dp(100);
	fill(dp.begin(), dp.end(), 100); 
	
	// 2. 离散化
	// 值域 1e9、元素个数 1e5 的线段树、树状数组题目常用。
	vector<int> vals = {500, 10, 1000000000, 10, 500, 999};
	
	// 第一步：排序
	sort(vals.begin(), vals.end());
	// 第二步：去重
	vals.erase(unique(vals.begin(), vals.end()), vals.end());
	
	// 第三步：查询 500 离散化后的编号，从 1 开始
	int old_val = 500;
	int new_id = lower_bound(vals.begin(), vals.end(), old_val) - vals.begin() + 1;
	// 结果 new_id = 2
}
