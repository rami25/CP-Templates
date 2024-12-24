template <auto P>
struct Mint {
	using Mtype = decltype(P);
	Mtype x;

	Mint(int64_t _x = 0) : x(norm(_x)) {}

    Mtype norm(int64_t k) {
        if (!(-P <= k && k < P)) k %= P;
        if (k < 0) k += P;
        return k;
    }

    Mint<P> inv() const {
        Mtype a = x, b = P, _x = 0, _y = 1;
        while (a != 0) { 
			Mtype k = b / a;
			b -= k * a;
			_x -= k * _y;
			swap(a, b);
			swap(_x, _y);
		}
        return Mint<P>(_x);
    }

    Mtype val() const {
        return x;
    }

    explicit operator int() const { return x; }
    explicit operator unsigned() const { return x; }
    explicit operator int64_t() const { return x; }
    explicit operator uint64_t() const { return x; }
    explicit operator double() const { return x; }
    explicit operator long double() const { return x; }

    Mint<P> operator-() const {
        return Mint<P>(-x);
    }
    Mint<P> &operator*=(const Mint<P> &rhs) {
        x = int64_t(x) * rhs.x % P;
        return *this;
    }
    Mint<P> &operator+=(const Mint<P> &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Mint<P> &operator-=(const Mint<P> &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Mint<P> &operator/=(const Mint<P> &rhs) {
        return *this *= rhs.inv();
    }
    friend Mint<P> operator*(const Mint<P> &lhs, const Mint<P> &rhs) {
        Mint<P> res = lhs;
        res *= rhs;
        return res;
    }
    friend Mint<P> operator+(const Mint<P> &lhs, const Mint<P> &rhs) {
        Mint<P> res = lhs;
        res += rhs;
        return res;
    }
    friend Mint<P> operator-(const Mint<P> &lhs, const Mint<P> &rhs) {
        Mint<P> res = lhs;
        res -= rhs;
        return res;
    }
    friend Mint<P> operator/(const Mint<P> &lhs, const Mint<P> &rhs) {
        Mint<P> res = lhs;
        res /= rhs;
        return res;
    }
    friend istream &operator>>(istream &is, Mint<P> &a) {
        int64_t v;
        is >> v;
        a = Mint<P>(v);
        return is;
    }
    friend ostream &operator<<(ostream &os, const Mint<P> &a) {
        return os << a.val();
    }
};

template<auto P>
Mint<P> power(Mint<P> a, int64_t b) {
    Mint<P> res(1);
    while (b) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

template<auto P>
string to_string(const Mint<P> &x) { 
	return to_string(x.val()); 
}

template <const int &MOD>
struct combinatorics {
	using comb_int = Mint<MOD>;
	vector<comb_int> fac, inv, ifac;

	combinatorics(int n = 1) {
		fac.resize(n+1);
		ifac.resize(n+1);
		inv.resize(n+1);
		fac[0] = ifac[0] = inv[1] = 1;
		for(int i = 2; i <= n; i++) 
			inv[i] = inv[MOD % i] * (MOD - MOD / i);
		for(int i = 1; i <= n; i++) {
			fac[i] = fac[i - 1] * i;
			ifac[i] = ifac[i - 1] * inv[i];
		}
	}

	comb_int fact(int n) {
		if (n < 0) return 0;
		return fac[n];
	}

	comb_int inv_fact(int n) {
		if (n < 0) return 0;
		return ifac[n];
	}

	comb_int choose (int n, int k) {
		if (n < k || k < 0) return 0;
		return fac[n] * ifac[n-k] * ifac[k];
	}

	comb_int perm (int n, int k) {
		if (n < k || k < 0) return 0;
		return fac[n] * ifac[n-k];
		return 0;
	}

	comb_int inv_choose(int n, int k) {
		assert(0 <= k && k <= n);
		return ifac[n] * fac[n-k] * fac[k];
	}

	comb_int inv_perm(int n, int k) {
		assert(0 <= k && k <= n);
		return ifac[n] * fac[n-k];
	}
};

const int MOD = int(1e9) + 7;

const int N = int(1e6);
combinatorics<MOD> comb(N);