template <class T = int, bool maximum = false> struct MQ { 
    const T INF = numeric_limits<T>::max()/2;
    queue<T> q;
    deque<T> m;
    
    MQ() {}

    MQ(const vector<T> &v) {
        for (T x : v) push(x);
    } 

    void push(T val) {
        q.push(val);
        if (maximum) {
            while (!m.empty() && m.back() < val) m.pop_back();
        } else {
            while (!m.empty() && m.back() > val) m.pop_back();
        }
        m.push_back(val);
    }

    void pop() {
        assert(!q.empty());
        if (q.front() == m.front()) m.pop_front();
        q.pop();
    }

    T get() {
        return m.empty() ? (maximum ? -INF : INF): m.front();
    }

    int size() {
        return q.size();
    }
};