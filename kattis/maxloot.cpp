#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 65;

int n;
long C;
long v[N], w[N];

void solve_small() {
	int L = n / 2, R = (n + 1) / 2;
	vector<pii> vec_l, vec_r;
	for(int bit = 0; bit < (1 << L); bit++) {
		long val = 0, weight = 0;
		for(int x = bit; x; x -= x & -x) {
			val += v[__builtin_ctz(x & -x)];
			weight += w[__builtin_ctz(x & -x)];
		}
		vec_l.emplace_back(weight, val);
	}
	for(int bit = 0; bit < (1 << R); bit++) {
		long val = 0, weight = 0;
		for(int x = bit; x; x -= x & -x) {
			val += v[__builtin_ctz(x & -x) + L];
			weight += w[__builtin_ctz(x & -x) + L];
		}
		vec_r.emplace_back(weight, val);
	}
	sort(vec_r.begin(), vec_r.end());
	for(int i = 1; i < vec_r.size(); i++)
		vec_r[i].y = max(vec_r[i].y, vec_r[i - 1].y);
	
	long ans = 0;
	for(pii p : vec_l) {
		auto it = upper_bound(vec_r.begin(), vec_r.end(), pii(C - p.x, 2e9 + 1));
		if(it == vec_r.begin()) continue;
		--it;
		ans = max(ans, p.y + it->y);
	}
	printf("%d\n", ans);
}

void solve_large() {
	long sum = 0;
	for(int i = 0; i < n; i++) sum += v[i];
	vector<vector<long>> dp(2, vector<long>(sum + 1, 1e18));
	dp[1][0] = 0;
	for(int i = 0; i < n; i++) {
		int now = i & 1, pre = now ^ 1;
		fill(dp[now].begin(), dp[now].end(), 1e18);
		for(int j = 0; j <= sum; j++) {
			dp[now][j] = min(dp[now][j], dp[pre][j]);
			if(j >= v[i])
				dp[now][j] = min(dp[now][j], dp[pre][j - v[i]] + w[i]);
		}
	}
	for(int i = sum; ~i; i--) if(dp[(n - 1) & 1][i] <= C) {
		printf("%d\n", i);
		return;
	}
}

void solve() {
	scanf("%d %lld", &n, &C);
	for(int i = 0; i < n; i++)
		scanf("%lld", v + i);
	for(int i = 0; i < n; i++)
		scanf("%lld", w + i);
	if (n <= 40) solve_small();
	else solve_large();
}

int T;

int main() {
	scanf("%d", &T);
	while(T--) solve();
	
	return 0;
}
