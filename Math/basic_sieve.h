vector<int> lpf;
vector<int> primes;
vector<int> phi; // totient function
vector<bool> prime;

void sieve(int N) {
	lpf.assign(N+1, 0);
	prime.assign(N+1, true);
	phi.assign(N+1, 0);
	iota(phi.begin(), phi.end(), 0);
	primes = {};
	prime[0] = prime[1] = false;
	for (int p = 2; p <= N; p++) {
		if (prime[p]) {
			lpf[p] = p;
			primes.push_back(p);
			phi[p] = p-1;

			for (ll i = p + p; i <= N; i += p) {
				prime[i] = false;
				lpf[i] = p;
				phi[i] -= phi[i] / p;
			}
		}
	}
}