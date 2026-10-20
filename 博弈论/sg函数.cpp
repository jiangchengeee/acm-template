#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int sg[N], f[105], k; // f 为允许的步数，需升序；k 为步数种类数
int vis[N];

void get_sg(int n) {
	for (int i = 1; i <= n; i++) {
		// 用时间戳代替 memset，标记一次 O(1)
		for (int j = 1; j <= k && f[j] <= i; j++) {
			vis[sg[i - f[j]]] = i;
		}
		// 求 mex
		for (int j = 0; ; j++) {
			if (vis[j] != i) {
				sg[i] = j;
				break;
			}
		}
	}
}
int main() {
	// 1. 初始化规则数组，必须升序
	k = 3;
	f[1] = 1; 
	f[2] = 3; 
	f[3] = 4;
	// sort(f + 1, f + 1 + k); // 规则未升序时需先排序
	
	// 2. 预处理 SG 函数
	// 设单堆石子最多 10000 个
	get_sg(10000); 
	
	// 3. 多堆石子异或和
	int m;
	cin >> m; // m 堆石子
	
	int ans = 0;
	for (int i = 1; i <= m; i++) {
		int a;
		cin >> a; // 这一堆有 a 个石子
		
		// 异或上该堆的 SG 值
		ans ^= sg[a]; 
	}
	
	// 4. 异或和非 0 先手必胜，否则后手必胜
	if (ans != 0) {
		cout << "先手必胜！" << endl;
	} else {
		cout << "后手必胜！" << endl;
	}
	
	return 0;
}
