struct CD { // 0-based
	vector<vector<int>> adj;
	vector<vector<int>> new_adj;
	vector<vector<int>> dist;
  	vector<int> par;
  	vector<int> sz;
	vector<int> depth;
  	vector<bool> vis;
	vector<int> leaves;
  	int n, root;

	CD() {}

	CD(int _n) {
		init(_n);
	}

	CD(const vector<vector<int>> &_adj) {
  	    init(_adj);
  	}

  	void init(int _n) {
		n = _n;
		adj = vector<vector<int>>(n, vector<int>());
		new_adj = vector<vector<int>>(n, vector<int>());
		dist = vector<vector<int>>(__lg(n)+1, vector<int>(n, 0));
  	  	vis.resize(n);
  	  	par.resize(n);
  	  	sz.resize(n);
		depth.resize(n);
  	}

  	void init(const vector<vector<int>> &_adj) {
  	    init(int(_adj.size()));
  	    adj = _adj;
  	}

  	void add_edge(int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
  	}

	void build() {
		root = init_centroid();
	}

  	int find_size(int v, int p, int h) {
		if (vis[v]) return 0;
		if (~h) dist[h][v] = dist[h][p] + 1; 
  	  	sz[v] = 1;
  	  	for (int x: adj[v]) {
			if (x != p) {
				sz[v] += find_size(x, v, h);
			}
  	  	}
  	  	return sz[v];
  	}

  	int find_centroid(int v, int p, int n) {
		for (int x: adj[v]) {
			if (x != p) {
				if (!vis[x] && sz[x] > n) {
					return find_centroid(x, v, n);
				}
			}
  	  	}
  	  	return v;
  	}

  	int init_centroid(int v = 0, int p = -1, int d = 0) {
		int c = find_centroid(v, p, find_size(v, p, ~p?depth[p]:-1)>>1);
  	  	vis[c] = true;
  	  	par[c] = p;
		depth[c] = d;

		bool isLeaf = 1;
  	  	for (int x: adj[c]) {
			if (!vis[x]) {
				isLeaf = 0;
				new_adj[c].push_back(x);
				new_adj[x].push_back(c);
				init_centroid(x, c, d+1);
			}
  	  	}
		if(isLeaf) leaves.push_back(c);
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

	int operator[](int u) {
		return par[u]; 
	}
};