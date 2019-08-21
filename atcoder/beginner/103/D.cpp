#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

int n, m;
vector<pii> isl;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0, a, b; i < m; i++) {
		scanf("%d%d", &a, &b);
		isl.emplace_back(a, b);
	}
	sort(isl.begin(), isl.end());
	int ans = 1;
	int l = isl[0].x, r = isl[0].y;
	for(int i = 1; i < isl.size(); i++) {
		//printf("%d %d\n", l, r);
		if(l >= isl[i].y || isl[i].x >= r) {
			ans++;
			l = isl[i].x, r = isl[i].y;
		} else {
			l = max(l, isl[i].x);
			r = min(r, isl[i].y);
		}
	}

	printf("%d", ans);

	return 0;
}
