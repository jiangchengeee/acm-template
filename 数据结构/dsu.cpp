#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
struct DSU {
	vector<int> pa;
	vector<int> sz; // sz[i] 表示以 i 为根的集合大小
	int set_count;       // 当前的集合（连通块）数量
	DSU(int n) {
		pa.resize(n + 1);
		sz.assign(n + 1, 1);
		iota(pa.begin(), pa.end(), 0);
		set_count = n; // 初始时有 n 个独立集合（这里默认忽略索引 0 或者将 0 当作独立点视具体题意而定，通常可以直接用）
	}
	int find(int x) {
		if (pa[x] == x) {
			return x;
		}
		return pa[x] = find(pa[x]); 
	}
	bool join(int x, int y) {
		int root_x = find(x);
		int root_y = find(y);
		if (root_x == root_y) {
			return false; 
		}
		// 启发式合并：保证 root_x 是较大的集合
		if (sz[root_x] < sz[root_y]) {
			std::swap(root_x, root_y);
		}
		pa[root_y] = root_x;
		sz[root_x] += sz[root_y];
		set_count--; 
		
		return true;
	}
	// 查询 x 所在集合的大小
	int get_size(int x) {
		return sz[find(x)];
	}
	// 查询当前还有多少个集合
	int get_set_count() const {
		return set_count;
	}
};
