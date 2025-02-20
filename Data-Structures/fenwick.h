template <class T = int> struct fenwick {
	int n;
	vector<T> bit, val;
	fenwick() {};
	fenwick(int _n) {
		n = _n+1; 
		bit.resize(n+1);
		val.resize(n+1);
	}
	fenwick(const vector<T> &v){ 
		n = int(v.size());
		val = v;
		bit = v; bit.insert(bit.begin(), 0);
		for(int pos = 1; pos <= n; pos++){
			int parent = pos+(pos&-pos);
			if(parent <= n) bit[parent] += bit[pos];
		}
	}

	void add(int pos, T delta) {
		val[pos] += delta;
		for (pos++; pos <= n; pos += pos&-pos) bit[pos] += delta;
	}

	void add(int l, int r, T delta) {
		add(l, delta);
		add(r+1, -delta);
	}

	void set(int pos, T v) {
		add(pos, v - val[pos]);
	}

	T get(int pos) {
		return val[pos];
	}

	T query(int pos) {
		T res = 0;
		for (pos++; pos; pos -= pos&-pos) res += bit[pos];
		return res;
	}

	T query(int l, int r) { // [l, r]
		return query(r) - query(l-1);
	}
};