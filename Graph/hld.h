// i will try to use the iterative version of segtree with lazy propagation ;)

template <class Info, class Tag> struct lsegtree { 
    int n;
    vector<Info> st;
    vector<Tag> tag;
    lsegtree() : n(0) {}
    lsegtree(int _n, Info e = Info()) : lsegtree(vector(_n, e)) {}
	template <typename T>
    lsegtree(const vector<T> &v) : n(int(v.size())) {
        st.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) return st[p] = v[l], void();
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }

    void pull(int p) {
        st[p] = st[2 * p] + st[2 * p + 1];
    }

    void apply(int p, const Tag &v, int l, int r) {
        st[p].apply(v, l, r);
        tag[p].apply(v);
    }

    void push(int p, int l, int m, int r) {
        apply(2 * p, tag[p], l, m);
        apply(2 * p + 1, tag[p], m, r);
        tag[p] = Tag();
    }

    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            st[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p, l, m, r);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }

    void modify(int l, int r, const Tag &v) {
        return modify(1, 0, n, l, r, v);
    }
    void modify(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v, l, r);
            return;
        }
        int m = (l + r) / 2;
        push(p, l, m, r);
        modify(2 * p, l, m, x, y, v);
        modify(2 * p + 1, m, r, x, y, v);
        pull(p);
    }

    Info query(int l, int r) {
		assert(0 <= l && l <= r; && r <= n);
		if (l == r) return Info();
        return query(1, 0, n, l, r);
    }
    Info query(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return st[p];
        }
        int m = (l + r) / 2;
        push(p, l, m, r);
        return query(2 * p, l, m, x, y) + query(2 * p + 1, m, r, x, y);
    }

    template<class F>
    int find_first(int l, int r, F &&f) {
        return find_first(1, 0, n, l, r, f);
    }
    template<class F>
    int find_first(int p, int l, int r, int x, int y, F &&f) {
        if (l >= y || r <= x || !f(st[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p, l, m, r);
        int res = find_first(2 * p, l, m, x, y, f);
        if (res == -1) {
            res = find_first(2 * p + 1, m, r, x, y, f);
        }
        return res;
    }

    template<class F>
    int find_last(int l, int r, F &&f) {
        return find_last(1, 0, n, l, r, f);
    }
    template<class F>
    int find_last(int p, int l, int r, int x, int y, F &&f) {
        if (l >= y || r <= x || !f(st[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p, l, m, r);
        int res = find_last(2 * p + 1, m, r, x, y, f);
        if (res == -1) {
            res = find_last(2 * p, l, m, x, y, f);
        }
        return res;
    }
};

template <class Info,
		  class Tag,
		  class T = int,
		  bool Edge = false> struct HLD {
	int n, cur_pos;
	vector<vector<int>> adj;
	vector<int> heavy;
	vector<int> head;
	vector<int> depth;
	vector<int> par;
	vector<int> sz;
	vector<int> tin, tout;
	vector<T> info, tour;
	lsegtree<Info, Tag> seg;

	HLD(int _n = 0) {
		n = _n;
		adj.assign(n, {});
		heavy.assign(n, -1);
		head.resize(n);
		depth.resize(n);
  	  	par.resize(n);
  	  	sz.resize(n);
		tin.resize(n);
		tout.resize(n);
	}

	HLD(const vector<vector<int>> &_adj) : HLD(int(_adj.size())) {
		adj = _adj;
	}

	void add_edge(int x, int y) {
		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	void build(const vector<T> &_info, int root = 0) {
		cur_pos = 0;
		info = _info;
		dfs_sz(root, -1);
		dfs_hld(root, root);
		seg = lsegtree<Info, Tag>(tour);
	}

	void dfs_sz(int v, int p) {
		par[v] = p;
		depth[v] = p < 0 ? 0 : depth[p] + 1;
		sz[v] = 1;
		int mx_sz = 0;
		for (int u : adj[v]) {
			if (u^p) {
				dfs_sz(u, v);
				sz[v] += sz[u];
				if (mx_sz < sz[u]) {
					mx_sz = sz[u];
					heavy[v] = u;
				}
			}
		}
	}

	void dfs_hld(int v, int p) {
		head[v] = p;
		tin[v] = cur_pos++;
		tour.emplace_back(info[v]);
		if (~heavy[v]) {
			dfs_hld(heavy[v], p);
		}
		for (int u : adj[v]) {
			if (u^par[v] && u^heavy[v]) {
				dfs_hld(u, u);
			}
		}
		tout[v] = cur_pos;
	}

	template <class F>
	int process_path(int x, int y, F &&f) {
		for (; head[x] != head[y]; y = par[head[y]]) {
			if (depth[head[x]] > depth[head[y]]) swap(x, y);
			f(tin[head[y]], tin[y] + 1);
		}
		if (depth[x] > depth[y]) swap(x, y);
		f(tin[x] + Edge, tin[y] + 1);
		return x;
	}

	int lca(int x, int y) {
		return process_path(x, y, [](int, int) -> void {});
	}

	int dist(int x, int y) {
		return depth[x] + depth[y] - 2 * depth[lca(x, y)];
	}

	Info query_path(int x, int y) {
		Info res = Info();
		process_path(x, y, [&](int l, int r) {
			res = res + seg.query(l, r);
		});
		return res;
	}

	void modify_path(int x, int y, const Tag &p) {
		process_path(x, y, [&](int l, int r) {
			seg.modify(l, r, p);
		});
	}

	void modify_node(int v, const Info &p) {
		seg.modify(tin[v], p);
	}

	Info query_subtree(int v) {
		return seg.query(tin[v] + Edge, tout[v]);
	}

	void modify_subtree(int v, const Tag &p) {
		seg.modify(tin[v] + Edge, tout[v], p);
	}
};

struct Tag {
	Tag() {}

    void apply(const Tag &t) {
		// TODO
    }
};

struct Info {
    Info() {}
    
    void apply(const Tag &t, int l, int r) {
		// TODO
    }
};

Info operator+(const Info &a, const Info &b) {
    Info c;
	// TODO
    return c;
}
