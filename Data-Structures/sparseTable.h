template <class T, class F> struct sparseTable { 
    int n;
    vector<vector<T>> st;
	F fun;
    
    sparseTable() {}

    sparseTable(const vector<T> &v, const F &f) : fun(f) {
        n = int(v.size());
        st = vector<vector<T>>(__lg(n)+1, vector<T>(n));
        st[0] = v;
        for (size_t i = 1; i < st.size(); i++) {
            for (int j = 0; j+(1<<i) <= n; j++) {
				st[i][j] = fun(st[i-1][j], st[i-1][j+(1<<(i-1))]);
			}
        }
    } 

    T query(int l, int r) { // [l, r)
        assert(0 <= l && l < r && r <= n);
        int sz = __lg(r-l);
        return fun(st[sz][l], st[sz][r - (1 << sz)]);
    }
};
