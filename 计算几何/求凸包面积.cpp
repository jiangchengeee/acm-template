#include <bits/stdc++.h>
using namespace std;
// 若已经写过「凸包（单调链法）」那份板子，下面这段 Point / cross 可以删掉，直接用那一份
const double eps = 1e-9;
struct Point {
	double x, y;
	Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
	Point operator - (const Point& b) const { return Point(x - b.x, y - b.y); }
};
// 叉积：a 叉乘 b
double cross(const Point& a, const Point& b) {
	return a.x * b.y - a.y * b.x;
}
// 叉积：p0->p1 与 p0->p2，>0 左转，<0 右转，==0 共线
double cross(const Point& p0, const Point& p1, const Point& p2) {
	return cross(p1 - p0, p2 - p0);
}

// 传入多边形的顶点数组 p（不要求首尾点重合，只要是顺时针或逆时针按顺序排列即可）
// 返回多边形的面积（鞋带公式）
double polygon_area(const vector<Point>& p) {
	int n = p.size();
	if (n < 3) return 0.0;
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += cross(p[i], p[(i + 1) % n]);
	}
	return fabs(sum) / 2.0;
}

signed main() {
	vector<Point> p = {{0, 0}, {4, 0}, {4, 3}, {0, 3}};   // 4 x 3 的矩形
	cout << fixed << setprecision(2) << polygon_area(p) << '\n';
	return 0;
}
/*
12.00
*/
