/**
 * 扩展欧几里得算法 (EXGCD)
 * 求解 ax + by = gcd(a, b) 的一组特解 (x, y)，并返回 gcd(a, b)
 */
int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}