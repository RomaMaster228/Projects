#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

bool dfs(int v, int par, const vector<vector<int>>& graph, vector<int>& color, vector<int>& res) {
	if (color[v] == 1) {
		return true;
	}
	if (color[v] == 2) {
		return false;
	}
	color[v] = 1;
	for (int to : graph[v]) {
		if (to != par && dfs(to, v, graph, color, res)) {
			res.push_back(to + 1);
			return true;
		}
	}
	color[v] = 2;
	return false;
}

int main() {
	int n;
	cin >> n;
	vector<vector<int>> graph(n);
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	vector<int> color(n);
	vector<int> res;
	if (dfs(0, 0, graph, color, res)) {
		set<int> s;
		s.insert(res[0]);
		for (int i = 1; i < res.size(); i++) {
			if (res[0] == res[i]) {
				break;
			}
			else {
				s.insert(res[i]);
			}
		}
		for (const auto& i : s) {
			cout << i << " ";
		}
	}
	else {
		cout << "-1 ";
	}
	cout << '\n';
}

