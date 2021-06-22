#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9 + 7;

struct Edge {
	int a, b, c; //begin,end,cost
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	int n, m, s;
	cin >> n >> m >> s;
	s--;
	vector<Edge> E;
	for (int i = 0; i < m; i++) {
		Edge e;
		cin >> e.a >> e.b >> e.c;
		e.a--; e.b--;
		E.push_back({ e.a,e.b,e.c });
		E.push_back({ e.b,e.a,e.c });
	}
	vector<int> d(n, INF);
	d[s] = 0;
	
	for (int i = 0; i < n - 1; i++) {
		bool ok = false;
		for (const Edge& e : E) {
			if (d[e.a] == INF) {
				continue;
			}
			if (d[e.b] > d[e.a] + e.c) {
				ok = true;
				d[e.b] = d[e.a] + e.c;
			}
		}
		if (ok == false) {
			break;
		}
	}
	for (int i = 0; i < n; i++) {
		if (d[i] == INF) {
			cout << -1 << " ";
		}
		else {
			cout << d[i] << " ";
		}
	}
	return 0;
}
