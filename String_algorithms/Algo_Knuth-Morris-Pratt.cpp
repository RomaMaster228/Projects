#include <iostream>
#include <vector>
#include <algorithm>
#include <clocale>
using namespace std;

vector<int> prefix_function(string s) {
	int n = s.size();
	vector<int> pi(n);
	for (int i = 1; i < n; i++) {
		int j = pi[i - 1];
		while (j > 0 && s[i] != s[j]) {
			j = pi[j - 1];
		}
		if (s[i] == s[j]) {
			j++;
		}
		pi[i] = j;
	}
	return pi;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	//setlocale(LC_ALL, "rus");
	string t, p;
	cin >> t >> p;//t-текст,p-образ(подстрока)
	vector<int> v = prefix_function(p);
	int l = 0;
	int k = 0;
	int cnt = 0;
	while (k < t.size()) {
		if (t[k] == p[l]) {
			k++;
			l++;
			if (l == p.size()) {
				cnt++;
			}
		}
		else if (l == 0) {
			k++;
		}
		else {
			l = v[l - 1];
		}
	}
	if (cnt != 0) {
		cout << "Yes" << '\n';
		cout << cnt << '\n'; // how many repetitions
	}
	else {
		cout << "No" << '\n';
	}
	return 0;
}


