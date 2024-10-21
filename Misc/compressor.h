template <class T> struct compressor { 
	vector<T*> v;
	void operator+=(T &x) { v.push_back(&x); }

	T operator() (T init = T()) {
		sort(v.begin(), v.end(), [](int *x, int *y) { return *x < *y; });
		T last = 0, q = 0;
		for (size_t i = 0; i < v.size(); i++) {
			if (!i || *v[i] != last) q++;
			last = *v[i];
			*v[i] = q - 1 + init;
		}
		return q;
	}
};