#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long
mt19937_64 gen(12345);
const int N=5e5+5,mod=1e9+7,inf=1e9+7;
int n,m,q,k;
int a[N],b[N],c[N];
typedef struct liner_basis{
	int basis[70]={0},cnt=0,d[70]={0};
	bool has_zero=false;
	bool insert(int x){//是否成功插入可用于查询是否能异或出某值
		for(int i=63;i>=0;i--){
			if((x>>i)&1){
				if(!basis[i]){
					basis[i]=x;
					return 1;//成功插入
				}
				x^=basis[i];
			}
		}
		has_zero=1;
		return 0;//插入失败
	}
	int qmax() {
		int res = 0;
		for (int i = 63; i >= 0; i--) {
			if ((res ^ basis[i]) > res) {
				res ^= basis[i];
			}
		}
		return res;
	}
	int qmin() {
		for (int i = 0; i <= 63; i++) {
			if (basis[i]) {
				return basis[i];
			}
		}
		return 0; // 整个线性基为空的情况
	}	
	void rebuild() {//使用查询前必须重构
		// 从高位到低位，用较低位的基底消去较高位基底中冗余的 1
		for (int i = 63; i >= 0; i--) {
			for (int j = i - 1; j >= 0; j--) {
				if ((basis[i] >> j) & 1) {
					basis[i] ^= basis[j];
				}
			}
		}
		cnt = 0;
		for (int i = 0; i <= 63; i++) {
			if (basis[i]) {
				d[cnt++] = basis[i];
			}
		}
	}
	int lower_query(int k) {//查询第k小的值
		if (has_zero) {
			k--;
		}
		if (k == 0) return 0;
		if (k >= (1LL << cnt)) return -1;
		int res = 0;
		for (int i = 0; i < cnt; i++) {
			if ((k >> i) & 1) {
				res ^= d[i];
			}
		}
		return res;
	}	
	int upper_query(int k){
		int total = (1ll << cnt) - 1 + has_zero; 
		if (k <= 0 || k > total) return -1; // 超出范围返回 -1
		return lower_query(total - k + 1);  // 转化为求第 (total - k + 1) 小
	}
}lb;
//合并把其中一个线性基里的所有有效基底，依次 insert 到另一个线性基里就可以了。
void solve(){
	lb a{};
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		a.insert(x);
	}
	cout<<a.qmax()<<'\n';
}
signed main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
//    cin >> t;
    while (t--){
		solve();
    }
//    system("x-www-browser https://ys.mihoyo.com/");
    return 0;
}
/*
1
5
2 3
0 0
4 5
0 0
0 0

*/
