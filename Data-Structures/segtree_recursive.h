template<class Info> struct segtree { 
    int n;
    vector<Info> st;
    segtree() : n(0) {}
    segtree(int _n, Info e = Info()) : segtree(vector(_n, e)) {}
	template <typename T>
    segtree(const vector<T> &v) : n(int(v.size())) {
        st.assign(4 << __lg(n), Info());
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) return st[p] = v[l], void();
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }

    void pull(int p) {
        st[p] = st[2 * p] + st[2 * p + 1];
    }

    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) return st[p] = v, void();
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }

    Info query(int l, int r) {
        return query(1, 0, n, l, r);
    }
    Info query(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) return Info();
        if (l >= x && r <= y) return st[p];
        int m = (l + r) / 2;
        return query(2 * p, l, m, x, y) + query(2 * p + 1, m, r, x, y);
    }

    template<class F>
    int find_first(int l, int r, F &&f) {
        return findFirst(1, 0, n, l, r, f);
    }
    template<class F>
    int find_first(int p, int l, int r, int x, int y, F &&f) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !f(st[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, f);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, f);
        }
        return res;
    }

    template<class F>
    int find_last(int l, int r, F &&f) {
        return findLast(1, 0, n, l, r, f);
    }
    template<class F>
    int find_last(int p, int l, int r, int x, int y, F &&f) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !f(st[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, f);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, f);
        }
        return res;
    }
};

struct Info {
	Info () {}
};

Info operator+(const Info &a, const Info &b) {
	Info res;
	// merging operation
	return res;
}