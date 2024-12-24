template <class T>
struct edge {
	int to;
	T cost;
	edge() {}
	edge(int to, T cost) : to(to), cost(cost) {}
};

template <class T = long long, bool directed = false>
struct DJ { 
    int n;
    vector<vector<edge<T>>> adj;
    const T INF = numeric_limits<T>::max()/2;

    DJ() {}

    DJ(int _n) {
        n = _n;
        adj.resize(n);
    }

    DJ(const vector<vector<edge<T>>> &_adj) {
		n = int(_adj.size());
		adj = _adj;
    }

    void add_edge(int from, int to, T dist) {
        adj[from].emplace_back(to, dist);
        if (!directed) adj[to].emplace_back(from, dist);
    }

    vector<T> dist(const vector<int> &sources) {
        vector<T> res(n, INF);
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
        for (int src : sources) {
            res[src] = 0;
            pq.push({0, src});
        }
        while (!pq.empty()) {
            auto cur = pq.top(); pq.pop();
            if (cur.first > res[cur.second]) continue;
            for (auto e : adj[cur.second]) {
                if (res[e.to] > cur.first + e.cost) {
                    res[e.to] = cur.first + e.cost;
                    pq.push({res[e.to], e.to});
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (res[i] == INF) res[i] = -1;
        }
        return res;
    }

    T dist(int src, int dest) {
        return dist({src})[dest];
    }

    pair<T, vector<int>> path(int src, int dest) {
        // Return the distance from src to dest, along with a shortest path
        vector<T> res(n, INF);
        vector<int> prv(n);
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
        res[src] = 0;
        pq.push({0, src});
        while (!pq.empty()) {
            auto cur = pq.top(); pq.pop();
            if (cur.first > res[cur.second]) continue;
            for (auto e : adj[cur.second]) {
                if (res[e.to] > cur.first + e.cost) {
                    res[e.to] = cur.first + e.cost;
                    prv[e.to] = cur.second;
                    pq.push({res[e.to], e.to});
                }
            }
        }
        if (res[dest] == INF) return make_pair(-1, vector<int>());
        vector<int> path = {dest};
        while (path.back() != src) path.push_back(prv[path.back()]);
        reverse(path.begin(), path.end());
        return make_pair(res[dest], path);
    }
};