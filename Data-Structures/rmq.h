template <class T = int, bool maximum_mode = false> struct RMQ { // 0-based
	int n;
	vector<vector<T>> rmq;

	RMQ() {}

  	RMQ(const vector<T> &v) {
		n = int(v.size());
        rmq = vector<vector<T>>(__lg(n)+1, vector<T>(n));
		rmq[0] = v;
  	  	for (int i = 0; i < int(rmq.size())-1; ++i) {
			for (int j = 0; j <= n - (1 << i); ++j) {
  	    	  rmq[i + 1][j] = op(rmq[i][j], rmq[i][j + (1 << i)]);
  	    	}
		}
  	}

  	T query(int a, int b) const { // [a, b)
        assert(0 <= a && a < b && b <= n);
  	  	int dep = 31 - __builtin_clz(b - a); 
  	  	return op(rmq[dep][a], rmq[dep][b - (1 << dep)]);
  	}

	static T op(T a, T b) {
		return maximum_mode? max(a, b) : min(a, b);
	}
};