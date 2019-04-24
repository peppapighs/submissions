#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, k, ans;
int A[N], l[N], r[N];
vector<int> vec;
set<pii> S;

int main() {
	scanf("%d %d", &n, &k);
	for(int i = 1, a, b; i <= n; i++) {
		scanf("%d", &a);
		if(i != 1) A[i] = a - b;
		if(i > 2) l[i] = i-1;
		if(i != n) r[i] = i+1;
		b = a;
	}
	for(int i = 2; i <= n; i++) S.emplace(A[i], i);
	for(int i = 1, a, b; i <= k; i++) {
		int now = S.begin()->y;
		ans += A[now];
		a = l[now], b = r[now];
		S.erase(pii(A[now], now));
		if(a) S.erase(pii(A[a], a));
		if(b) S.erase(pii(A[b], b));
		A[now] = A[a] + A[b] - A[now];
		if(a && b) {
			l[now] = l[a], r[now] = r[b];
			S.emplace(pii(A[now], now));
		} else now = 0;
		if(l[a]) r[l[a]] = now;
		if(r[b]) l[r[b]] = now;
	}
	printf("%d\n", ans);

	return 0;
}