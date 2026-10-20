template <typename T>
struct SegTree {
    struct Node {
        T w, tag;
    };
    int n;
    std::vector<Node> t;
    
    SegTree(int n_ = 0) { init(n_); }
    SegTree(const std::vector<T>& a) { init(a); }
    
    void init(int n_) {
        n = n_;
        t.assign(4 * n + 1, {0, 0});
    }
    
    void init(const std::vector<T>& a) {
        n = a.size() - 1; // 默认 a 是 1-indexed
        t.assign(4 * n + 1, {0, 0});
        auto build = [&](auto &&self, int u, int l, int r) -> void {
            if (l == r) { t[u].w = a[l]; return; }
            int mid = (l + r) >> 1;
            self(self, u << 1, l, mid);
            self(self, u << 1 | 1, mid + 1, r);
            pushup(u);
        };
        build(build, 1, 1, n);
    }
    
    inline void pushup(int u) {
        // 合并由加法改为求 max
        t[u].w = std::max(t[u << 1].w, t[u << 1 | 1].w);
    }

    // 区间加法对 max 的影响无需长度 len
    inline void maketag(int u, T x) {
        t[u].tag += x;
        t[u].w += x;
    }
    
    // pushdown 也不再需要 l 和 r 参数
    inline void pushdown(int u) {
        if (t[u].tag) {
            maketag(u << 1, t[u].tag);
            maketag(u << 1 | 1, t[u].tag);
            t[u].tag = 0;
        }
    }
    
    void update(int u, int l, int r, int ql, int qr, T x) {
        if (ql <= l && r <= qr) {
            maketag(u, x);
            return;
        }
        pushdown(u);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(u << 1, l, mid, ql, qr, x);
        if (qr > mid) update(u << 1 | 1, mid + 1, r, ql, qr, x);
        pushup(u);
    }

    T query(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return t[u].w;
        pushdown(u);
        int mid = (l + r) >> 1;
        
        // 采用分支返回，避免初始化极小值（如 -INF）带来的数据类型边界麻烦
        if (ql <= mid && qr > mid) {
            return std::max(query(u << 1, l, mid, ql, qr), 
                            query(u << 1 | 1, mid + 1, r, ql, qr));
        } else if (ql <= mid) {
            return query(u << 1, l, mid, ql, qr);
        } else {
            return query(u << 1 | 1, mid + 1, r, ql, qr);
        }
    }
    
    void update(int ql, int qr, T x) { update(1, 1, n, ql, qr, x); }
    T query(int ql, int qr) { return query(1, 1, n, ql, qr); }
};