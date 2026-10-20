#include <bits/stdc++.h>
using namespace std;

// ==========================================
// 1. 声明与初始化
// ==========================================
void vector_init() {
	// 基础一维
	vector<int> v1;                    // 空 vector
	vector<int> v2(10);                // 长度为 10，默认全为 0
	vector<int> v3(10, -1);            // 长度为 10，全部初始化为 -1
	vector<int> v4 = {1, 2, 3, 4, 5};  // 列表初始化
	vector<int> v5(v4.begin() + 1, v4.end()); // 截取初始化 (2,3,4,5)
	
	// 二维及多维
	vector<vector<int>> mat1(5, vector<int>(5, 0)); // 5x5 矩阵，全为 0
	vector<int> adj[100005];           // 邻接表，最常用的存图方式
	vector<vector<pair<int, int>>> graph(100005); // 带权图邻接表
}

// ==========================================
// 2. 容量与内存
// ==========================================
void vector_memory() {
	vector<int> v;
	
	// reserve 与 resize 的区别
	v.reserve(100000); // 预分配内存，size 仍为 0，避免反复扩容
	v.resize(100000);  // size 变为 10 万，新元素默认填 0
	
	// 空间释放
	v.clear();         // size 变 0，capacity 通常不释放
	v.shrink_to_fit(); // C++11，将 capacity 缩小到 size
	vector<int>().swap(v); // 彻底释放内存的惯用法
}

// ==========================================
// 3. 增删改
// ==========================================
void vector_modifiers() {
	vector<int> v = {1, 2, 3, 4, 5};
	
	// 尾部操作
	v.push_back(6);
	v.emplace_back(7); // C++11，原地构造，存结构体时优于 push_back
	v.pop_back();      // 删除最后一个元素，不返回该元素
	
	// 插入与删除，复杂度 O(N)
	v.insert(v.begin() + 2, 99); // 在索引 2 前面插入 99
	v.erase(v.begin() + 1);      // 删除索引 1 的元素
	v.erase(v.begin() + 1, v.begin() + 3); // 删除区间 [1, 3)
	
	// 不关心元素顺序时，可 O(1) 删除指定位置：
	// 与末尾元素交换后 pop_back
	int idx_to_remove = 2; 
	swap(v[idx_to_remove], v.back());
	v.pop_back();
}

// ==========================================
// 4. 与 Algorithm 库配合
// ==========================================
void vector_algorithms() {
	vector<int> v = {5, 2, 8, 2, 9, 1};
	
	// 1. 最值与求和
	int max_val = *max_element(v.begin(), v.end()); // 找最大值
	int min_val = *min_element(v.begin(), v.end()); // 找最小值
	long long sum = accumulate(v.begin(), v.end(), 0LL); // 求和，注意第三个参数 0LL 防溢出
	
	// 2. 排序与翻转
	sort(v.begin(), v.end());             // 升序
	sort(v.rbegin(), v.rend());           // 降序
	reverse(v.begin(), v.end());          // 翻转整个 vector
	
	// 3. 离散化去重
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	
	// 4. 二分查找 (要求序列有序)
	// lower_bound 找第一个 >= x 的位置
	int pos1 = lower_bound(v.begin(), v.end(), 5) - v.begin(); 
	// upper_bound 找第一个 > x 的位置
	int pos2 = upper_bound(v.begin(), v.end(), 5) - v.begin(); 
}

// ==========================================
// 5. vector<bool>
// ==========================================
void vector_bool_warning() {
	// vector<bool> 是位压缩特化，每个 bool 占 1 bit。
	// 省空间，但速度慢，且不能取元素的指针或引用。
	vector<bool> vb(100, false); 
	
	// 需要速度时改用 vector<char> 或 vector<int>
	vector<char> fast_bool(100, 0); 
}
