#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void dfs(int v, const vector<vector<int>>& graph, vector<bool>& used, vector<int>& levels, vector<int>& path) {
	if (used[v]) {
		return;
	}
	used[v] = 1;
	for (int to : graph[v]) {
		dfs(to, graph, used, levels, path);
		if (levels[to] >= levels[v]) {
			levels[v] = levels[to] + 1;
			path[v] = to;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> graph(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
	}
	vector<bool> used(n);
	vector<int> path(n, -1);
	vector<int> levels(n);
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs(i, graph, used, levels, path);
		}
	}
	int mx = -1;
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (levels[i] > mx) {
			mx = levels[i];
			cnt = i;
		}
	}
	cout << mx + 1 << '\n';
	for (int i = cnt; i != -1; i = path[i]) {
		cout << i + 1 << " ";
	}
	cout << '\n';
	return 0;
}

