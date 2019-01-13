#include <bits/stdc++.h>

#define pll pair<long long, long long>
#define x first
#define y second

using namespace std;

const int N = 5e4+5;
const int M = 1 << 20;

int n, ptr;
long long dp[N];
pll t[M << 1];
vector<pll> A, rect;

long long f(pll a, long long x) { return a.x*x + a.y; }

void add(pll now, int p = 1, int l = 1, int r = M) {
	int m = (l+r) >> 1;
	bool left = f(now, l) < f(t[p], l);
	bool mid = f(now, m) < f(t[p], m);
	if(mid) swap(now, t[p]);	
	if(l == r) return;
	else if(left != mid) add(now, p<<1, l, m);
	else add(now, p<<1|1, m+1, r);
}

long long query(long long x, int p = 1, int l = 1, int r = M) {
	int m = (l+r) >> 1;
	if(l == r) return f(t[p], x);
	if(x <= m) return min(f(t[p], x), query(x, p<<1, l, m));
	else return min(f(t[p], x), query(x, p<<1|1, m+1, r));
}

int main() {
	fill(begin(t), end(t), pll(0, 1e12));
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		long long a, h, w;
		scanf("%lld %lld %lld", &a, &h, &w);
		A.emplace_back(w, a*h);
	}
	sort(A.begin(), A.end(), greater<pll>());
	long long mx = 0LL;
	int cnt = 0;
	rect.emplace_back(0LL, 0LL);
	for(pll p : A) if(p.y > mx) {
		rect.emplace_back(p);
		mx = p.y;
		cnt++;
	}
	for(int i = 1; i <= cnt; i++) {
		add(pll(rect[i].x, dp[i-1]));
		dp[i] = query(rect[i].y);
	}
	printf("%lld\n", dp[cnt]);

	return 0;
}