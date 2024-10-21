template <typename T = long long, class Compare = std::less<T>> struct topK { 
    multiset<T, Compare> s;
    size_t k;
    T total = 0;
    typename multiset<T, Compare>::iterator it;

    topK(int _k = 1) : k(_k) {}

    void insert(T x) {
        s.insert(x);
        if (s.size() <= k) total += x;
        else if (Compare{}(x, *it)) total += x - *it--;
        if (s.size() == k) it = prev(s.end());
    }

    void erase(T x) {
        if (s.size() <= k) s.erase(s.lower_bound(x)), total -= x;
        else {
            auto it2 = s.lower_bound(x);
            if (Compare{}(x, *it)) total += *++it - x;
            s.erase(it2);
        } 
    }
};