// Source: https://github.com/atcoder/ac-library

template <class Info> struct segtree { 
  public:
    segtree() : segtree(0) {}
    explicit segtree(int n, Info e = Info()) : segtree(vector<Info>(n, e)) {}
	template <typename T>
    explicit segtree(const vector<T> &v) : _n(int(v.size())) {
		log = ceil(log2(_n));
        size = 1 << log;
        d = vector<Info>(2 * size, Info());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void modify(int p, const Info &x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    Info get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    Info query(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        Info sml = Info(), smr = Info();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = sml + d[l++];
            if (r & 1) smr = d[--r] + smr;
            l >>= 1;
            r >>= 1;
        }
        return sml + smr;
    }

    Info root() const { return d[1]; }

    template <bool (*f)(Info)> int max_right(int l) const {
        return max_right(l, [](Info x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(Info()));
        if (l == _n) return _n;
        l += size;
        Info sm = Info();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(sm + d[l])) {
                while (l < size) {
                    l = (2 * l);
                    if (f(sm + d[l])) {
                        sm = sm + d[l];
                        l++;
                    }
                }
                return l - size;
            }
            sm = sm + d[l];
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(Info)> int min_left(int r) const {
        return min_left(r, [](Info x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(Info()));
        if (r == 0) return 0;
        r += size;
        Info sm = Info();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(d[r] + sm)) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(d[r] + sm)) {
                        sm = d[r] + sm;
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = d[r] + sm;
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    vector<Info> d;

    void update(int k) { d[k] = d[2 * k] + d[2 * k + 1]; }
};

struct Info {
	Info() {}
};

Info operator+(const Info &a, const Info &b) {
	Info res;
	// todo
	return res;
}