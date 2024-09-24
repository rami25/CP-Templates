struct dsu { 
	int n;
	vector<int> p;
	dsu(int n) : n(n), p(n, -1) {}

	int get(int x){
		assert(0 <= x && x < n);
		return p[x] < 0? x : p[x] = get(p[x]);
	}

	bool merge(int x, int y){
		assert(0 <= x && x < n);
		assert(0 <= y && y < n);
		x = get(x), y = get(y);
		if(x == y) return false;
		if(p[x] > p[y]) swap(x, y);
		p[x] += p[y];
		p[y] = x;
		return true;
	}

	bool same(int x, int y){
		assert(0 <= x && x < n);
		assert(0 <= y && y < n);
		return get(x) == get(y);
	}

	int size(int x){
		assert(0 <= x && x < n);
		return -p[get(x)];
	}
};