#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long INF = 1e18 + 14;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	string s, t;
	cin >> s >> t;
	const long long p = 31;
	vector<long long> p_pow(max(s.length(), t.length()));
	p_pow[0] = 1;
	for (long long i = 1; i < p_pow.size(); ++i) {
		unsigned long long z = ((p_pow[i - 1] % INF) * (p % INF)) % INF;
		p_pow[i] = z % INF;
	}
	vector<long long> h(t.length());
	for (long long i = 0; i < t.length(); ++i)
	{
		h[i] = (((t[i] - 'a' + 1) % INF) * (p_pow[i] % INF) % INF);
		if (i)  h[i] += h[i - 1];
	}
	long long h_s = 0;
	long long cnt = 0;
	for (long long i = 0; i < s.length(); ++i)
		h_s += (((s[i] - 'a' + 1) % INF) * (p_pow[i] % INF)) % INF;
	for (long long i = 0; i + s.length() - 1 < t.length(); ++i)
	{
		long long cur_h = h[i + s.length() - 1];
		if (i)  cur_h -= h[i - 1];
		if (cur_h == h_s * p_pow[i] % INF)
			cnt++;
	}
	cout << cnt << '\n';
	return 0;
}