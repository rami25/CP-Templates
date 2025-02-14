template <class Info, class Tag> struct lsegtree { 
    int n;
    vector<Info> st;
    vector<Tag> tag;
    lsegtree() : n(0) {}
    lsegtree(int _n, Info e = Info()) : lsegtree(vector(_n, e)) {}
	template <typename T>
    lsegtree(const vector<T> &v) : n(int(v.size())) {
        st.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());
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

    void apply(int p, const Tag &v, int l, int r) {
        st[p].apply(v, l, r);
        tag[p].apply(v);
    }

    void push(int p, int l, int m, int r) {
        apply(2 * p, tag[p], l, m);
        apply(2 * p + 1, tag[p], m, r);
        tag[p] = Tag();
    }

    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            st[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p, l, m, r);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }

    void modify(int l, int r, const Tag &v) {
        return modify(1, 0, n, l, r, v);
    }
    void modify(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v, l, r);
            return;
        }
        int m = (l + r) / 2;
        push(p, l, m, r);
        modify(2 * p, l, m, x, y, v);
        modify(2 * p + 1, m, r, x, y, v);
        pull(p);
    }

    Info query(int l, int r) {
        return query(1, 0, n, l, r);
    }
    Info query(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return st[p];
        }
        int m = (l + r) / 2;
        push(p, l, m, r);
        return query(2 * p, l, m, x, y) + query(2 * p + 1, m, r, x, y);
    }

    template<class F>
    int find_first(int l, int r, F &&f) {
        return find_first(1, 0, n, l, r, f);
    }
    template<class F>
    int find_first(int p, int l, int r, int x, int y, F &&f) {
        if (l >= y || r <= x || !f(st[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p, l, m, r);
        int res = find_first(2 * p, l, m, x, y, f);
        if (res == -1) {
            res = find_first(2 * p + 1, m, r, x, y, f);
        }
        return res;
    }

    template<class F>
    int find_last(int l, int r, F &&f) {
        return find_last(1, 0, n, l, r, f);
    }
    template<class F>
    int find_last(int p, int l, int r, int x, int y, F &&f) {
        if (l >= y || r <= x || !f(st[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p, l, m, r);
        int res = find_last(2 * p + 1, m, r, x, y, f);
        if (res == -1) {
            res = find_last(2 * p, l, m, x, y, f);
        }
        return res;
    }
};

struct Tag {
	Tag() {}

    void apply(const Tag &t) {
		// TODO
    }
};

struct Info {
    Info() {}
    
    void apply(const Tag &t, [[maybe_unused]]int l, [[maybe_unused]]int r) {
		// TODO
    }
};

Info operator+(const Info &a, const Info &b) {
    Info c;
	// TODO
    return c;
}