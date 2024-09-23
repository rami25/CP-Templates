// source : https://github.com/the-tourist/algo/blob/master/data/disjointsparsetable.cpp

template <typename T = int> struct DST { // 0-indexed
	T op (T a, T b) const {
		return min(a,b); 
	}
	int n;
	vector<vector<T>> mat;

	DST () {}

	DST (const vector<T> &a) : n(int(a.size())) {
		mat.push_back(a);
		for (int p = 1; (1 << p) < n; p++) {
			mat.emplace_back(n);
			for (int mid = 1 << p; mid < n; mid += 1 << (p + 1)) {
				mat[p][mid - 1] = a[mid - 1];
				for (int j = mid - 2; j >= mid - (1 << p); j--) {
					mat[p][j] = op(a[j], mat[p][j + 1]);
				}
				mat[p][mid] = a[mid];
				for (int j = mid + 1; j < min(n, mid + (1 << p)); j++) {
					mat[p][j] = op(mat[p][j - 1], a[j]);
				}
			}
		}
	}

	T query (int l, int r) const { // [l, r)
	  assert(0 <= l && l < r && r <= n);
	  if (r - l == 1) {
		return mat[0][l];
	  }
	  int p = bit_width(unsigned(l ^ (r - 1))) - 1;
	  return op(mat[p][l], mat[p][r - 1]);
	}

	int bit_width(unsigned x) const {
		return x == 0 ? 0 : 32 - __builtin_clz(x);
	}
};
