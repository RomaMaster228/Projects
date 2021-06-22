#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs(int st, const vector<vector<int> >& graph, vector<int>& dist, vector<int>& path) {
	dist.assign(graph.size(), -1);
	queue<int> q;
	q.push(st);
	dist[st] = 0;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int to : graph[v]) {
			if (dist[to] != -1) {
				continue;
			}
			path[to] = v;
			dist[to] = dist[v] + 1;
			q.push(to);
		}
	}

}

int main() {
	int n, m, u;
	cin >> n >> m >> u;
	u--;
	vector<vector<int>> graph(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	vector<int> dist(n);
	vector<int> path(n, -1);
	bfs(u, graph, dist, path);
	for (const int& cur : dist) {
		cout << cur << " ";
	}
	cout << '\n';
	return 0;
}
