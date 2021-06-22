#include <iostream>
#include <vector>

using namespace std;

void dfs(int v, const vector<vector<int> >& graph, vector<int>& used, int& cnt) {
	if (used[v] != -1) {
		return;
	}
	used[v] = cnt;
	cnt++;
	for (int to : graph[v]) {
		dfs(to, graph, used, cnt);
	
	}

}

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	k--;
	vector<vector<int>> graph(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	vector<int> used(n,-1);
	int cnt = 0;
    dfs(k, graph, used, cnt);
	for (int i = 0; i < n; i++) {
		cout << used[i] << " ";
	}
	cout << '\n';
	return 0;
}

