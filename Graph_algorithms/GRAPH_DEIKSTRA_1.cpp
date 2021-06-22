#include <iostream>
#include <vector>
using namespace std;
/std:c++17
const int INF = 1e9 + 7;

struct Edge {
	int to, c; //to,cost
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	int n, m, s;
	cin >> n >> m >> s;
	s--;
	vector<vector<Edge>> G(n);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		G[a].push_back({ b,c });
		G[b].push_back({ a, c });
	}
	vector<int> d(n, INF);
	vector<bool> used;
	d[s] = 0;
	for (int i = 0; i < n; i++) {
		int u = -1;
		for (int j = 0; j < n; j++) {
			if (!used[j] && (u == -1 || d[j] < d[u])) {
				u = j;
			}
			if (d[u] == INF) {
				break;
			}
			used[u] = 1;
			for (auto [to, cost] : G[u]) {
				if (d[to] > d[u] + cost) {
					d[to] = d[u] + cost;
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (d[i] == INF) {
			cout << "-1" << " ";
		}
		else {
			cout << d[i] << " ";
		}
	}
	return 0;
}