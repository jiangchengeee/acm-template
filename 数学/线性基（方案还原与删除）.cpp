#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
mt19937_64 gen(12345);
const int N=1e5+5,LOG=64;
int n,m,q,k;
typedef struct liner_basis{
	int basis[LOG]={0};//基向量
	bitset<N> src[LOG];//每个基向量由哪些原始元素异或而成
	bitset<N> dead;//已被删除的元素编号
	int val[N]={0};//编号->值
	int tot=0;//已插入的元素个数（编号1..tot）
	int add(int x,int id)//核心插入：值x、编号id；线性无关返回1
	{
		int path[LOG],pc=0,j=-1,y=x;
		for(int i=LOG-1;i>=0;i--){
			if((y>>i)&1){
				if(!basis[i]){j=i;break;}//找到空位，说明线性无关
				y^=basis[i],path[pc++]=i;
			}
		}
		if(j<0)return 0;//线性相关：删它不影响张成空间，来源不必记
		bitset<N> s;s.set(id);
		up(t,0,pc-1)s^=src[path[t]];//按消元路径异或出这一位的来源
		basis[j]=y,src[j]=s;
		return 1;
	}
	int insert(int x){tot++;val[tot]=x;add(x,tot);return tot;}//返回新元素的编号
	void erase(int id){if(!dead.test(id))dead.set(id);}//O(1)删除，不重建
	void rebuild_all()//只在必要时才重建：用还活着的元素重算线性基
	{
		memset(basis,0,sizeof(basis));
		up(i,0,LOG-1)src[i].reset();
		up(i,1,tot)if(!dead.test(i))add(val[i],i);
	}
	bool which(int x,bitset<N>&res)//x能否被活着的元素异或出来；能则res给出是哪些
	{
		res.reset();
		int y=x;
		for(int i=LOG-1;i>=0;i--){
			if((y>>i)&1){
				if(!basis[i])return 0;
				y^=basis[i],res^=src[i];
			}
		}
		if((res&dead).any()){//答案里用到了已删元素，这时才不得不重建
			rebuild_all();
			return which(x,res);//重建后来源全是活着的，最多递归一层
		}
		return 1;//没碰到已删元素，答案直接可信，不需要任何重建
	}
	bool can(int x){//x能不能被异或出来
		if(dead.none()){//还没删过东西，消到0就一定能表示
			for(int i=LOG-1;i>=0;i--){
				if((x>>i)&1){
					if(!basis[i])return 0;
					x^=basis[i];
				}
			}
			return 1;
		}
		bitset<N> s;
		return which(x,s);
	}
	vector<int> list_of(bitset<N>&res)//把来源bitset转成编号列表
	{
		vector<int>v;
		up(i,1,tot)if(res.test(i))v.push_back(i);
		return v;
	}
	int qmax()//最大异或和
	{
		int res=0;
		bitset<N> s;
		for(int i=LOG-1;i>=0;i--){
			if((res^basis[i])>res)res^=basis[i],s^=src[i];
		}
		if((s&dead).any()){//最大值用到了已删元素，重建后再算
			rebuild_all();
			return qmax();
		}
		return res;
	}
}lb;
lb A;//必须开成全局：src是 bitset<N>[64]，放函数里会爆栈

void solve(){
	int q;
	cin>>n>>q;
	up(i,1,n){int x;cin>>x;A.insert(x);}
	while(q--){
		int op,x;
		cin>>op>>x;
		if(op==1)A.insert(x);//插入
		else if(op==2)A.erase(x);//按编号删除（O(1)，不重建）
		else if(op==4)cout<<A.qmax()<<'\n';//最大异或和
		else{//查询x能被哪些元素异或出来
			bitset<N> s;
			if(!A.which(x,s))cout<<-1<<'\n';
			else{
				vector<int>v=A.list_of(s);
				cout<<v.size();
				for(auto id:v)cout<<' '<<id;
				cout<<'\n';
			}
		}
	}
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
4 6
1 2 4 8
3 5
4 0
2 1
3 5
4 0
3 6
// 2 1 3    （5 = val[1]^val[3] = 1^4）
// 15       （1^2^4^8）
// -1       （删掉1号后 {2,4,8} 只能凑偶数，5 凑不出来）
// 14       （2^4^8）
// 2 2 3    （6 = 2^4）

P3812 【模板】线性基 P4570 [BJWC2011] 元素
*/
