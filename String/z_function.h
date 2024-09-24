namespace z { 
	using str = const string&; 

	vector<int> z_algo(str s) {
		int n = int(s.size());
		if (n == 0) return {};
		vector<int> z(n);
		for (int l = 0, r = 0, i = 1; i < n; i++) {
			z[i] = max(0, min(z[i-l], r-i+1));
			while (i+z[i] < n && s[i+z[i]] == s[z[i]]) {
				l = i; r = i+z[i]; z[i]++;
			}
		}
		z[0] = n;
		return z;
	}

	bool is_substring(str s, str t) {
		int n = int(s.size()), m = int(t.size());
		if (n >= m) return s == t;
	  	string st;
	  	for (auto x: s) st.push_back(x);
	  	for (auto x: t) st.push_back(x);
	  	vector<int> z = z_algo(st);
	  	for (int i = n; i < n + m; ++i) {
	  	  if (z[i] >= n) return true;
	  	}
	  	return false;
	}

	vector<int> search(str s, str t) {
		int n = int(s.size()), m = int(t.size());
	  	string st;
	  	for (auto x: s) st.push_back(x);
	  	for (auto x: t) st.push_back(x);
	  	vector<int> z = z_algo(st), occs;
	  	for (int i = n; i < n + m; ++i) {
	  	  if (z[i] >= n) occs.push_back(i-n);
	  	}
		return occs;
	}
}