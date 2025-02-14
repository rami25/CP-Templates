template <typename T> T modular_inverse(T a, T m) {
    T u = 0, v = 1;
    while (a != 0) {
		T k = m / a;
		m -= k * a;
		u -= k * v;
		swap(a, m);
		swap(u, v);
    }
    assert(m == 1);
    return u;
}

template <typename T, typename U> T power(T a, U b) {
	T res = 1;
    while (b) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

template <auto P> struct Mint {
	using Mtype = decltype(P);

  public:
	Mint(int64_t _x = 0) : x(norm(_x)) {}

    explicit operator int() const { return x; }

	Mint<P> inv() const { Mtype a = modular_inverse(x, P); return Mint<P>(a); }

    Mint<P> operator-() const { return Mint<P>(-x); }

    Mint<P> &operator+=(const Mint<P> &rhs) { x = norm(x + rhs.x); return *this; }
    Mint<P> &operator-=(const Mint<P> &rhs) { x = norm(x - rhs.x); return *this; }
    Mint<P> &operator*=(const Mint<P> &rhs) { x = int64_t(x) * rhs.x % P; return *this; }
    Mint<P> &operator/=(const Mint<P> &rhs) { return *this *= rhs.inv(); }

	Mint<P> &operator++() { return *this += 1; }
	Mint<P> &operator--() { return *this -= 1; }

	friend Mint<P> operator++(Mint<P> &lhs, int) { Mint<P> res = lhs; ++lhs; return res; }
	friend Mint<P> operator--(Mint<P> &lhs, int) { Mint<P> res = lhs; --lhs; return res; }

    friend Mint<P> operator+(const Mint<P> &lhs, const Mint<P> &rhs) { return Mint<P>(lhs) += rhs; }
    friend Mint<P> operator-(const Mint<P> &lhs, const Mint<P> &rhs) { return Mint<P>(lhs) -= rhs; }
    friend Mint<P> operator*(const Mint<P> &lhs, const Mint<P> &rhs) { return Mint<P>(lhs) *= rhs; }
    friend Mint<P> operator/(const Mint<P> &lhs, const Mint<P> &rhs) { return Mint<P>(lhs) /= rhs; }

    friend ostream &operator<<(ostream &os, const Mint<P> &a) { return os << a.x; }
    friend istream &operator>>(istream &is, Mint<P> &a) { 
		int64_t v;
		is >> v;
		a = Mint<P>(v);
		return is; 
	}

  private:
	Mtype x;
    Mtype norm(int64_t k) {
		if (!(-P <= k && k < P)) k %= P;
		if (k < 0) k += P; 
		return k;
	}
};

const int MOD = int(1e9) + 7;
using mint = Mint<MOD>;