template <class T = int, bool maximum = false> struct RMQ { 
	int n;
	vector<vector<T>> rmq;

	RMQ() {}

  	RMQ(const vector<T> &v) : n(v.size()) {
        rmq = vector<vector<T>>(__lg(n)+1, vector<T>(n));
		rmq[0] = v;
  	  	for (size_t i = 1; i < rmq.size(); i++) {
			for (int j = 0; j+(1<<i) <= n; j++) {
				rmq[i][j] = op(rmq[i-1][j], rmq[i-1][j + (1 << (i-1))]);
  	    	}
		}
  	}

  	T query(int l, int r) const { // [l, r)
        assert(0 <= l && l < r && r <= n);
        int sz = __lg(r-l);
  	  	return op(rmq[sz][l], rmq[sz][r - (1 << sz)]);
  	}

	static T op(const T &a, const T &b) {
		return maximum ? max(a, b) : min(a, b);
	}
};
