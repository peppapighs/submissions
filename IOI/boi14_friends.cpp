#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e6 + 5;

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

pii prm(69, 1337);
pii pwr[N];

int n, mid;
pii dp[N];
char A[N];
map<pii, pii> ans;

int main() {
	pwr[0] = pii(1, 1);
	for(int i = 1; i < N; i++) pwr[i] = mul(pwr[i - 1], prm);

	scanf("%d", &n);
	if(!(n & 1)) return !printf("NOT POSSIBLE");
	mid = n >> 1;
	scanf("%s", A + 1);

	for(int i = 1; i <= n; i++) dp[i] = add(mul(dp[i - 1], prm), pii(A[i], A[i]));
	for(int i = 1; i <= n; i++) {
		pii lhs, rhs;
		if(i <= mid) {
			lhs = add(mul(dp[i - 1], pwr[mid - i + 1]), sub(dp[mid + 1], mul(dp[i], pwr[mid - i + 1])));
			rhs = sub(dp[n], mul(dp[mid + 1], pwr[mid]));
			if(lhs == rhs && !ans.count(lhs)) ans[lhs] = pii(mid + 2, n);
		} else {
			lhs = dp[mid];
			rhs = add(mul(sub(dp[i - 1], mul(dp[mid], pwr[i - mid - 1])), pwr[n - i]), sub(dp[n], mul(dp[i], pwr[n - i])));
			if(lhs == rhs && !ans.count(lhs)) ans[lhs] = pii(1, mid);
		}
	}

	if(!ans.size()) return !printf("NOT POSSIBLE");
	else if(ans.size() == 1) for(int i = ans.begin()->y.x; i <= ans.begin()->y.y; i++) printf("%c", A[i]);
	else if(ans.size() > 1) return !printf("NOT UNIQUE");

	return 0;
}