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

struct LCA {  
    int n, Log;
    vector<vector<int>> up;
    vector<vector<int>> adj;
    vector<int> depth, tin, tout;
    vector<pair<int, int>> tour;
	RMQ<pair<int,int>> rmq;
    
	LCA() {}

    LCA(int _n) {
        n = _n;
		Log = __lg(n);
        up = vector<vector<int>>(Log+1, vector<int>(n, -1));
        adj.resize(n);
        depth.resize(n);
        tin.resize(n);
        tout.resize(n);
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
		rmq = RMQ<pair<int,int>>(tour);
    }

	void dfs(int v, int p, int d) {
        tin[v] = tout[v] = tour.size();
        tour.emplace_back(d, v);
        depth[v] = d;
        up[0][v] = p;
		for (int i = 1; i <= Log; i++) {
			if (~up[i-1][v]) {
				up[i][v] = up[i-1][up[i-1][v]];
			}
		}
        for (int u : adj[v]) {
			if (u^p) {
                dfs(u, v, d+1);
                tout[v] = tour.size();
                tour.emplace_back(d, v);
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
        x = tin[x], y = tin[y];
        if (x > y) swap(x, y);
        return rmq.query(x, y+1).second;
    }

    int dist(int x, int y) {
        return depth[x] + depth[y] - 2 * depth[lca(x, y)];
    }

    bool is_ancestor(int x, int y) {
        // Returns whether x is an ancestor of y
        return tin[x] <= tin[y] && tin[y] <= tout[x];
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

    // Returns a vector of nodes, and a vector of (parent, child) in virtual tree
    pair<vector<int>, vector<pair<int, int>>> virtual_tree(vector<int> nodes) {
        auto &&sort_by_preorder = [&](int a, int b) { return tin[a] < tin[b]; };
        sort(nodes.begin(), nodes.end(), sort_by_preorder);
        int sz = nodes.size();
        for (int i=0; i+1<sz; i++) nodes.push_back(lca(nodes[i], nodes[i+1]));
        sort(nodes.begin(), nodes.end(), sort_by_preorder);
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        vector<pair<int, int>> res;
        res.reserve(nodes.size() - 1);
        for (int i=1; i<int(nodes.size()); i++) res.emplace_back(lca(nodes[i-1], nodes[i]), nodes[i]);
        return make_pair(nodes, res);
    }
};
