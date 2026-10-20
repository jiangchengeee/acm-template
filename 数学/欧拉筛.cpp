#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int p[N], phi[N], cnt;//phi表示欧拉函数
bool vis[N];

void init(int n) {
	phi[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) {
			p[++cnt] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= cnt && i * p[j] <= n; j++) {
			vis[i * p[j]] = 1;
			if (i % p[j] == 0) {
				phi[i * p[j]] = phi[i] * p[j];
				break;
			}
			phi[i * p[j]] = phi[i] * (p[j] - 1);
		}
	}
}
