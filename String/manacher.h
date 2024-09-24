namespace manacher { 
	using str = const string&;

	vector<int> init(str s) {
		int n = int(s.size());
		vector<int> p(2 * n + 1);
		for (int i = 1, j = -1, r = 0; i < 2 * n; i++, j--) {
			if (i > r) {
				r = i + 1, p[i] = 1;
			} else {
				p[i] = p[j];
			}
			if (i + p[i] >= r) {
				int b = r >> 1, a = i - b;
				while (a > 0 && b < n && s[a - 1] == s[b]) {
					a--, b++;
				}
				p[i] = b - a, j = i, r = b << 1;
			}
		}
		return p;
	}

	string lps(str s) { // longest palindromic substring
		vector<int> p = init(s);
		int maxi = 0;
		for (int i = 1; i < int(p.size()); i++) {
			if (p[maxi] < p[i]) {
				maxi = i;
			}
		}
		return s.substr((maxi - p[maxi])/2, p[maxi]);
	}
}