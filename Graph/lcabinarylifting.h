struct LCA { 
    int n, Log;
    vector<vector<int>> up;
    vector<vector<int>> adj;
    vector<int> depth;
    
	LCA() {}

    LCA(int _n) {
		n = _n;
		Log = __lg(n);
        up = vector<vector<int>>(Log+1, vector<int>(n, -1));
        adj.resize(n);
        depth.resize(n);
    }

	LCA(const vector<vector<int>> &_adj) : LCA(int(_adj.size())) {
		adj = _adj;
	}

    void add_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }


    void build(int root = 0) {
        dfs(root, -1, 0);
    }

    void dfs(int v, int p, int d) {
        depth[v] = d;
		up[0][v] = p; 
        for (int i = 1; i <= Log ; i++) {
			if (~up[i-1][v]) {
				up[i][v] = up[i-1][up[i-1][v]];
			}
		}
        for (int u : adj[v]) {
			if (u^p) {
				dfs(u, v, d+1);
			}
        }
    }

    int ancestor(int v, int k) { 
		for (int i = 0; i <= Log && ~v; i++) {
            if (k & (1<<i)) v = up[i][v];
        }
        return v;
    }

    int lca(int x, int y) {
        if (depth[x] < depth[y]) swap(x, y);
        x = ancestor(x, depth[x]-depth[y]);
        if (x == y) return x;
		for (int i = Log; i >= 0; i--) {
            if (up[i][x] != up[i][y]) {
                x = up[i][x];
                y = up[i][y];
            }
        }
        return up[0][x];
    }

    int dist(int x, int y) {
        return depth[x] + depth[y] - 2 * depth[lca(x, y)];
    }

    int find_on_path(int x, int y, int k) {
        // Find the k-th (1-indexed) node on the path from x to y
        // Return -1 if no node exists
        int l = lca(x, y);
        int d = depth[x] + depth[y] - 2 * depth[l];
        if (k > d+1) return -1;
        if (depth[x] - depth[l] >= k) return ancestor(x, k-1);
        return ancestor(y, d-k+1);
    }
};
