struct dsu { 
	int n;
	vector<int> p;
	dsu(int n = 0) : n(n), p(n, -1) {}

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

template <class T> struct MST { 
    int n;
	vector<pair<T, pair<int, int>>> chosen;
	vector<pair<T, pair<int, int>>> edges;
	dsu d;
	MST() {}
	MST(int _n) {
		n = _n;
		d = dsu(n);
	}
	void add_edge(int x, int y, T z) {
		edges.push_back({z, {x, y}});
	}
	T mst() {
		sort(edges.begin(), edges.end());
		T res = 0;
        for (auto edge : edges) {
            if (d.merge(edge.second.first, edge.second.second)) {
                chosen.push_back(edge);
                res += edge.first;
            }
        }
        return (d.size(0) == n) ? res : -1;
	}
	vector<pair<T, pair<int,int>>> answer() { return chosen; }
};