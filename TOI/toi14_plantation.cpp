#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int T;
pii P[N];

long d(pii a, pii b) { return 1LL*(a.x-b.x)*(a.x-b.x) + 1LL*(a.y-b.y)*(a.y-b.y); }

long solve(int l, int r) {
	if(l == r) return LLONG_MAX;
	if(l == r-1) return d(P[l], P[r]);
	int m = (l + r) >> 1;
	long left = solve(l, m), right = solve(m+1, r);
	long del = min(left, right);
	int bar = P[m].x;
	vector<pii> ap;
	for(int i = l; i <= r; i++) if(d(P[i], pii(bar, P[i].y)) <= del) ap.emplace_back(P[i]);
	for(int i = 0; i < ap.size(); i++)
		for(int j = i+1; j < ap.size(); j++)
			del = min(del, d(ap[i], ap[j]));

	return del;
}

int main() {
	scanf("%d", &T);
	while(T--) {
		int n, r, d;
		scanf("%d %d %d", &n, &r, &d);
		for(int i = 1; i <= n; i++) scanf("%d %d", &P[i].x, &P[i].y);
		sort(P+1, P+n+1);
		double ans = sqrt(1.0*solve(1, n));
		if(ans - 2.0*r < d) printf("N\n");
		else printf("Y\n");
	}

	return 0;
}
