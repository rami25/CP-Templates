struct CD { 
  	int n, root;
	vector<vector<int>> adj;
	vector<vector<int>> dist;
  	vector<int> par;
  	vector<int> sz;
	vector<int> depth;
  	vector<bool> vis;

	CD(int _n = 0) {
		n = _n;
		adj = vector<vector<int>>(n, vector<int>());
		dist = vector<vector<int>>(__lg(n)+1, vector<int>(n));
  	  	vis.resize(n);
  	  	par.resize(n);
  	  	sz.resize(n);
		depth.resize(n);
	}

	CD(const vector<vector<int>> &_adj) : CD(int(_adj.size())) {
  	    adj = _adj;
  	}

  	void add_edge(int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
  	}

	void build() {
		root = decompose(0, -1, 0);
	}

  	int get_sz(int v, int p, int h) {
		if (~h) dist[h][v] = dist[h][p] + 1; 
  	  	sz[v] = 1;
  	  	for (int u: adj[v]) {
			if (!vis[u] && u^p) {
				sz[v] += get_sz(u, v, h);
			}
  	  	}
  	  	return sz[v];
  	}

  	int get_centroid(int v, int p, int z) {
		for (int u: adj[v]) {
			if (!vis[u] && u^p && sz[u] > z) {
				return get_centroid(u, v, z);
			}
  	  	}
  	  	return v;
  	}

  	int decompose(int v, int p, int d) {
		int z = get_sz(v, p, ~p ? depth[p] : -1);
		int c = get_centroid(v, p, z >> 1);
  	  	vis[c] = true;
  	  	par[c] = p;
		depth[c] = d;

  	  	for (int u: adj[c]) {
			if (!vis[u]) {
				decompose(u, c, d+1);
			}
  	  	}
		return c;
  	}

	int lca(int u, int v) {
		if (depth[u] < depth[v]) swap(u, v);
		while (depth[u] != depth[v]) u = par[u];
		if (u == v) return u;
		while (u != v) {
			u = par[u];
			v = par[v];
		}
		return u;
	}

	int get_dist(int u, int v) {
		int l = lca(u, v);
		return dist[depth[l]][u] + dist[depth[l]][v];
	}

	int operator[](int u) { return par[u]; }
};
