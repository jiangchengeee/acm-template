#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
const int MAXN=5e5+5;              // 元素个数上限，按题目改
const int LOG=31;                  // 值域位宽：值 < 2^31 用 31；long long 全值域用 63
const int MAXNODE=MAXN*(LOG+1)+5;  // 节点数上界：每个数最多新增 LOG 个节点
// 01-trie：维护一个可重集，支持插入/删除/查询与给定值异或的最大值
// 注意 tr 和 cnt 显式用 int32_t：不然会被 #define int long long 拖成 8 字节一个，内存翻倍
struct orz_trie {
	int32_t tr[MAXNODE][2];// 儿子节点编号
	int32_t cnt[MAXNODE];  // 经过该节点的元素个数（删除就是把它减掉）
	int tot=0;             // 已分配的节点数
	int sz=0;              // 当前集合内的元素个数
	void init(){           // 多组数据时调用
		up(i,0,tot){
			tr[i][0]=tr[i][1]=0;
			cnt[i]=0;
		}
		tot=0,sz=0;
	}
	bool count(int x){     // x 是否在集合里
		int p=0;
		down(i,LOG-1,0){
			int bit=(x>>i)&1;
			if(!tr[p][bit])return 0;
			p=tr[p][bit];
		}
		return cnt[p]>0;
	}
	void update(int x, int delta){//delta=1插入，delta=-1删除
		if(delta<0&&!count(x))return;//删不存在的值会凭空建节点、把计数搞成负数，必须挡掉
		int p=0;
		down(i,LOG-1,0){
			int bit=(x>>i)&1;
			if(tr[p][bit]==0){
				tr[p][bit]=++tot;
			}
			p=tr[p][bit];
			cnt[p]+=delta;
		}
		sz+=delta;
	}
	int query(int x){      // 集合内元素与 x 异或的最大值
		if(sz==0)return 0;//空集
		int p=0, ma=0;
		down(i,LOG-1,0){
			int bit=(x>>i)&1;
			if(tr[p][bit^1]&&cnt[tr[p][bit^1]]>0){//优先走相反位
				ma|=1ll<<i;
				p=tr[p][bit^1];
			}else{
				p=tr[p][bit];
			}
		}
		return ma;
	}
}tri;
// 常见变体：查询第 k 小、统计异或和小于 x 的个数，都是在 query 的骨架上按 cnt 走
