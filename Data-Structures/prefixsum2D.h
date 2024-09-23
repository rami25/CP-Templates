template <class T = long long> struct psm { // 0-indexed
    vector<vector<T>> prefix;

    psm() {}

    psm(const vector<vector<T>> &v) {
        prefix = vector<vector<T>>(int(v.size())+1, vector<T>(int(v[0].size())+1));
        for (int i=0; i<int(v.size()); i++) {
            for (int j=0; j<int(v[0].size()); j++) 
				prefix[i+1][j+1] = prefix[i+1][j] + prefix[i][j+1] - prefix[i][j] + v[i][j];
        }
    }

    T query(int l1, int r1, int l2, int r2) {
        return prefix[r1+1][r2+1] - prefix[l1][r2+1] - prefix[r1+1][l2] + prefix[l1][l2];
    }
};