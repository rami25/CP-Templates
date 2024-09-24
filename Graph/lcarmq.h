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

struct LCA { // 0 or 1-indexed
    int n;
    vector<vector<int>> jump;
    vector<vector<int>> adj;
    vector<int> depth, tin, tout;
    vector<pair<int, int>> tour;
	RMQ<pair<int,int>> rmq;
    
	LCA() {}

    LCA(int _n) {
		init(_n);
	}

    LCA(const vector<vector<int>> &_adj) {
		init(_adj);
    }

	void init(int _n) {
        n = _n+1;
        jump = vector<vector<int>>(__lg(n-1)+1, vector<int>(n));
        adj.resize(n);
        depth.resize(n);
        tin.resize(n);
        tout.resize(n);
	}

	void init(const vector<vector<int>> &_adj) {
		init(int(_adj.size()));
		adj = _adj;
	}

    void add_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    void dfs(int cur, int parent = -1, int cur_depth = 0) {
        tin[cur] = tout[cur] = tour.size();
        tour.emplace_back(cur_depth, cur);
        depth[cur] = cur_depth;
        jump[0][cur] = parent;
        for (int i=1; i<int(jump.size()); i++) jump[i][cur] = jump[i-1][cur] == -1 ? -1 : jump[i-1][jump[i-1][cur]];
        for (int node : adj[cur]) {
            if (node != parent) {
                dfs(node, cur, cur_depth+1);
                tout[cur] = tour.size();
                tour.emplace_back(cur_depth, cur);
            }
        }
    }

    void build(int root = 1) {
        dfs(root);
		rmq = RMQ<pair<int,int>>(tour);
    }

    int ancestor(int node, int k) { // find k-th ancestor of node
        for (int i=0; i<int(jump.size()); i++) {
            if ((k&(1<<i)) && node != -1) node = jump[i][node];
        }
        return node;
    }

    int lca(int x, int y) {
        int a = tin[x], b = tin[y];
        if (a > b) swap(a, b);
        return rmq.query(a, b+1).second;
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