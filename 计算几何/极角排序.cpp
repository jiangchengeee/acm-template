#include <bits/stdc++.h>
using namespace std;
struct Point {
	long long x, y;
	
	// 1. 象限划分 / 半平面划分
	// 规定极角从 x 轴正半轴开始，逆时针方向为正。
	// 我们将平面分为上下两个半区：
	// 上半区 (包含正 x 轴)：y > 0，或者 y == 0 且 x > 0 (返回 0)
	// 下半区 (包含负 x 轴)：y < 0，或者 y == 0 且 x < 0 (返回 1)
	// 原点 (0,0) 通常特殊处理或不参与极角排序，这里默认归为上半区
	int half() const {
		if (y > 0 || (y == 0 && x > 0)) return 0;
		return 1;
	}
};

// 2. 叉积 (Cross Product): OA × OB
// 几何意义：以 OA 和 OB 为邻边的平行四边形的有向面积
// 如果结果 > 0，说明从 OA 到 OB 是逆时针方向 (A 的极角小于 B 的极角)
// 如果结果 < 0，说明是顺时针方向
// 如果结果 == 0，说明 A, O, B 三点共线
long long cross(Point a, Point b) {
	return a.x * b.y - a.y * b.x;
}

// 3. 距离平方 (用于共线时的副关键字排序)
long long dist2(Point a) {
	return a.x * a.x + a.y * a.y;
}

// 4. 极角排序比较函数（逆时针）
bool polar_cmp(Point a, Point b) {
	// 步骤一：如果两个点在不同的半区，上半区的点一定排在前面
	if (a.half() != b.half()) {
		return a.half() < b.half();
	}
	
	// 步骤二：如果在同一个半区，用叉积判断相对位置
	long long cp = cross(a, b);
	if (cp != 0) {
		// cp > 0 表示 a 在 b 的顺时针方向（即 a 的角度更小）
		return cp > 0; 
	}
	
	// 步骤三：如果极角完全相同 (共线)，通常把距离原点更近的点排在前面
	return dist2(a) < dist2(b);
}

// ==========================================
// 5. 用法示例
// ==========================================
void polar_sort_example() {
	vector<Point> pts = {
{-2, -2}, {1, 1}, {-1, 1}, {2, 0}, {0, 2}, {1, -1}
};
	
	// 假设以原点 (0,0) 为基准点进行极角排序
	// 如果基准点是其他的点 P，只需要把所有的点先减去 P (平移坐标系) 再排序即可
	sort(pts.begin(), pts.end(), polar_cmp);
	
	// 排序后的 pts 顺序将是严格的逆时针一圈
}
