#include <bits/stdc++.h>
using namespace std;

// ==========================================
// 计算几何：atan2 安全极角与扫描线极角排序
// ==========================================
const double PI = acos(-1.0);
const double eps = 1e-9;

// 浮点数比较函数（防精度误差）
int sgn(double x) {
	if (abs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}

struct Point {
	double x, y;
	
	// 核心改造：将 atan2 的 [-PI, PI] 强制映射到 [0, 2*PI)
	// 这样在极角扫描时角度单调递增，不会出现负数
	double angle() const {
		double ang = atan2(y, x);
		if (sgn(ang) < 0) ang += 2 * PI;
		return ang;
	}
	
	// 到原点的距离平方
	double dist2() const {
		return x * x + y * y;
	}
};

// ==========================================
// 浮点数极角排序比较器
// ==========================================
bool cmp_atan2(const Point& a, const Point& b) {
	double ang1 = a.angle();
	double ang2 = b.angle();
	
	// 如果极角不同，按极角升序
	if (sgn(ang1 - ang2) != 0) {
		return ang1 < ang2;
	}
	// 极角相同（共线），按距离原点从近到远排序
	return a.dist2() < b.dist2();
}

void atan2_example() {
	vector<Point> pts = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
	
	// 输出角度：转换为通俗易懂的度数 (180.0 / PI)
	for (auto p : pts) {
		cout << "点 (" << p.x << "," << p.y << ") 的极角是: " 
		<< p.angle() * 180.0 / PI << " 度\n";
	}
	// 预期输出: 45度, 135度, 225度, 315度（递增，无负数）
	
	sort(pts.begin(), pts.end(), cmp_atan2);
}
