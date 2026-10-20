// 传入多边形的顶点数组 p（不要求首尾点重合，只要是顺时针或逆时针按顺序排列即可）
// 返回多边形的面积
double polygon_area(const vector<Point>& p) {
    int n = p.size();
    if (n < 3) return 0.0; 
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += cross(p[i], p[(i + 1) % n]); 
    }
    return abs(sum) / 2.0; 
}