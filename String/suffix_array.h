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

template <typename T, int ALPHABET = 256> struct suffix_array { 
	int n, Log;
	T str;
	vector<int> sa; 
	vector<int> lcp_array; 
	vector<vector<int>> rnk;
	RMQ<int> rmq;

	suffix_array() {}

	suffix_array(T& _s, bool build_lcp_arr = false, bool build_rmq = false) {
		str = _s;
		str += "$";
		n = int(str.size());
		sa.resize(n);
		lcp_array.resize(n-1);
		Log = ceil(log2(n));
		rnk.assign(Log+1, vector<int>(n));
		build_suffix_array();
		if (build_lcp_arr) build_lcp_array(build_rmq);
	} 

    void build_suffix_array() { // O(N.log2(N))
    	vector<int> cnt(ALPHABET);
    	for (int i = 0; i < n; i++) cnt[str[i]]++;
    	for (int i = 1; i < ALPHABET; i++) cnt[i] += cnt[i-1];
    	for (int i = 0; i < n; i++) sa[--cnt[str[i]]] = i;

    	rnk[0][sa[0]] = 0;
    	for (int i = 1; i < n; i++) {
    		rnk[0][sa[i]] = rnk[0][sa[i-1]] + (str[sa[i]] != str[sa[i-1]]);
    	}

		vector<int> new_sa(n);
		for (int k = 0; (1 << k) < n; k++) {
		  for (int i = 0; i < n; i++) {
    	  	new_sa[i] = (sa[i] - (1 << k) + n) % n;
    	  }

    	  cnt.assign(n, 0);
    	  for (int i = 0; i < n; i++) cnt[rnk[k][i]]++;
    	  for (int i = 1; i < n; i++) cnt[i] += cnt[i-1];
    	  for (int i = n-1; i >= 0; i--) sa[--cnt[rnk[k][new_sa[i]]]] = new_sa[i];

    	  rnk[k+1][sa[0]] = 0;
    	  for (int i = 1; i < n; i++) {
    	  	pair<int,int> cur = {rnk[k][sa[i]], rnk[k][(sa[i] + (1 << k)) % n]};
    	  	pair<int,int> prev = {rnk[k][sa[i-1]], rnk[k][(sa[i-1] + (1 << k)) % n]};
    	  	rnk[k+1][sa[i]] = rnk[k+1][sa[i-1]] + (cur != prev);
    	  }
    	}
    }

	void build_lcp_array(bool build_rmq) { // O(N)
		int k = 0;
		for (int i = 0; i < n; i++) {
			if (rnk[Log][i] == n-1) {
				k = 0;
				continue;
			}
			int j = sa[rnk[Log][i]+1];
			while (i+k < n && j+k < n && str[i+k] == str[j+k]) k++;
			lcp_array[rnk[Log][i]] = k;
			if (k) k--;
		}
        if (build_rmq) rmq = RMQ<int>(lcp_array);
	}

	int ordered_lcp(int i, int j) { // 0-indexed on the suffix_array in O(1) 
		if (rnk[Log][sa[i]] > rnk[Log][sa[j]]) swap(i, j);
		return rmq.query(rnk[Log][sa[i]], rnk[Log][sa[j]]);
	}

	int lcp(int i, int j) { // 0-indexed on the original string in O(log2(N))
		int res = 0;
		for (int k = Log; k >= 0; k--) {
			if (rnk[k][i%n] == rnk[k][j%n]) {
				res += (1 << k);
				i += (1 << k);
				j += (1 << k);
			}
		}
		return res;
	}

	int compare(int i, int j, int len) { // 0-indexed on the original string in O(1)
		int sz = __lg(len);
		pair<int, int> a = {rnk[sz][i], rnk[sz][(i+len-(1 << sz))%n]};
		pair<int, int> b = {rnk[sz][j], rnk[sz][(j+len-(1 << sz))%n]};
		return a == b ? 0 : a < b ? -1 : 1;
	}
};