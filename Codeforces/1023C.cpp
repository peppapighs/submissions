#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define x first
#define y second

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

//-----------------------------------------------------------

int main() {
	int n, k, cnt = 0;
	vector<int> left;
	cin >> n >> k;
	string s;
	cin >> s;
	stack<int> S;
	S.emplace(-1);
	for(int i = 0; i < n; i++) {
		if(s[i] == '(' && cnt < k / 2) {
			left.emplace_back(i);
			S.emplace(i);
			cnt++;
		} else {
			if(S.top() != -1 && s[i] == ')') {
				S.pop();
				left.emplace_back(i);
			}
		}
	}
	sort(left.begin(), left.end());
	for(int p : left) printf("%c", s[p]);

	return 0;
}