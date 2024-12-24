// extended gcd
template <typename T>
T egcd(T a, T b, T &x, T &y) { 
	if(a < 0){
		T g = egcd(-a, b, x, y);
		x *= -1;
		return g;
	}
	if(b < 0){
		T g = egcd(a, -b, x, y);
		y *= -1;
		return g;
	}
	if(b == 0){
		x = 1, y = 0;
		return a;
	}
	T g = egcd(b, a % b, y, x);
	y -= (a / b) * x;
	return g;
}

// linear diophantine equation {ax + by = c}
template <typename T>
T lde(T a, T b, T c, T &x, T &y, bool &ch) {
	T g = egcd(a, b, x, y);
	if(ch = c % g == 0) {
		x *= c / g, y *= c / g;
	}
	return g;
} 

// linear modular equation {ax = b (mod n)}
template <typename T>
vector<T> lme(T a, T b, T n) {
	vector<T> res;
	T x, y;
	T g = egcd(a, n, x, y);
	if (b % g) return res;
	x = x * (b / g) % n;
	if (x < 0) x += n;
	for (int i = 0; i < g; i++) {
		res.push_back((x + i * n / g) % n);
	}
	return res;
}