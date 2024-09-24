namespace kmp { 
	using str = const string&;

	vector<int> pi(str s) {
		int n = int(s.size());
		vector<int> lps(n);
		for (int j = 0, i = 1; i < n; i++) {
			while (j > 0 && s[i] != s[j]) j = lps[j-1];
			if (s[i] == s[j]) j++;
			lps[i] = j;
		}
		return lps;
	}

	bool is_substring(str s, str t) {
		int n = (int)t.size();
		int m = (int)s.size();
		if (m >= n) return s == t;
		vector<int> lps = pi(s);
		for (int i = 0, j = 0; i < n; i++) {
			while (j > 0 && t[i] != s[j]) j = lps[j-1];
			if (t[i] == s[j]) j++;
			if (j == m) return true; 
		}
		return false;
	}

	vector<int> search(str s, str t) {
		int n = (int)t.size();
		int m = (int)s.size();
		vector<int> lps = pi(s), occs;
		for (int i = 0, j = 0; i < n; i++) {
			while (j > 0 && t[i] != s[j]) j = lps[j-1];
			if (t[i] == s[j]) j++;
			if (j == m) {
				occs.push_back(i-j+1);
				j = lps[j-1];
			}
		}
		return occs;
	}
}