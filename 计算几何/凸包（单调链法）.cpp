#pragma GCC optimize("O2")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define sm int,vector<int>,greater<int>
#define int long long
mt19937_64 gen(12345);
const int N=1e6+5,mod=998244353,inf=1e9+7;;
int n,m,q,k;
int a[N],b[N],c[N],d[N];
int gcd(int x,int y)
{
	if(y==0)return x;
	return gcd(y,x%y);
}
int ksm(int a,int n,int p)
{
	if(n<0)return 0;
	int res=1;
	while(n)
	{
		if(n&1)res=res*a%p;
		n>>=1;
		a=a*a%p;
	}
	return res;
}
const double eps = 1e-9;
int sgn(double x) {
	if (abs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}
struct Point {
	double x, y;
	Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
	
	// 向量减法，用于求叉积
	Point operator - (const Point& b) const {
		return Point(x - b.x, y - b.y);
	}
	
	//优先按 x 排序，x 相同按 y 排序
	bool operator < (const Point& b) const {
		if (sgn(x - b.x) == 0) return sgn(y - b.y) < 0;
		return sgn(x - b.x) < 0;
	}
	
	// 判等（用于去重）
	bool operator == (const Point& b) const {
		return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
	}
};

// 计算两个向量 a 和 b 的叉积
double cross(const Point& a, const Point& b) {
	return a.x * b.y - a.y * b.x;
}

// 计算向量 p0->p1 和 p0->p2 的叉积
// 返回值 > 0：p2 在 p0->p1 的左侧（向左转）
// 返回值 < 0：p2 在 p0->p1 的右侧（向右转）
// 返回值 == 0：三点共线
double cross(const Point& p0, const Point& p1, const Point& p2) {
	return cross(p1 - p0, p2 - p0);
}

// 输入点集 P，返回凸包上的点集（逆时针顺序，起点和终点不重合）
vector<Point> convex_hull(vector<Point>& P) {
	int n = P.size();
	if (n <= 2) return P; // 退化情况：点数小于等于2，本身就是凸包
	
	// 1. 排序并去重
	sort(P.begin(), P.end());
	P.erase(unique(P.begin(), P.end()), P.end());
	n = P.size();
	if (n <= 2) return P;
	
	vector<Point> hull(2 * n); // 用数组模拟栈，速度最快
	int top = 0;               // 栈顶指针，表示栈内元素个数
	
	// 2. 求下凸壳
	for (int i = 0; i < n; i++) {
		// 【核心判断】：如果向右转或共线，则弹栈
		// 注意：如果你需要保留凸包边上的共线点，把 <= 改成 < 即可
		while (top >= 2 && sgn(cross(hull[top - 2], hull[top - 1], P[i])) <= 0) {
			top--;
		}
		hull[top++] = P[i];
	}
	
	// 3. 求上凸壳
	int tmp = top; // 记录下凸壳的元素个数，上凸壳弹栈时不能破坏下凸壳
	for (int i = n - 2; i >= 0; i--) {
		while (top > tmp && sgn(cross(hull[top - 2], hull[top - 1], P[i])) <= 0) {
			top--;
		}
		hull[top++] = P[i];
	}
	
	// 4. 收尾：最后加入的起点与栈底的起点重合，需减去
	if (n > 1) top--;
	hull.resize(top); // 截断有效部分
	return hull;
}

void solve(){
	cin>>n;
	vector<Point>pts(n);
	up(i,0,n-1)
		cin>>pts[i].x>>pts[i].y;
	vector<Point>hull=convex_hull(pts);
	double ans=0;
	double tx=hull.back().x,ty=hull.back().y;
	for(auto const &[x,y]:hull){
		ans+=sqrt((x-tx)*(x-tx)+(y-ty)*(y-ty));
		tx=x;
		ty=y;
	}
	cout << fixed << setprecision(2) << ans << '\n';
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int t = 1;
//	cin >> t;
	while (t--){
		solve();
	}
//	system("x-www-browser https://ys.mihoyo.com/");
//	cout << fixed << setprecision(10) << x << '\n';
	return 0;
}
