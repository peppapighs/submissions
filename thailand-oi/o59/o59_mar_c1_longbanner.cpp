#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, h, l;
int ans;
int A[N], H[N], t[N];
vector<int> V;

int get(int x) { return lower_bound(V.begin(), V.end(), x) - V.begin(); }

void update(int x, int k) { for(int i = x+1; i < N; i += i&(-i)) t[i] += k; }

int query(int x) {
	int ret = 0;
	for(int i = x+1; i; i -= i&(-i)) ret += t[i];
	return ret;
}

int main() {
	scanf("%d %d %d", &n, &h, &l);
	for(int i = 1; i <= n; i++) scanf("%d %d", &A[i], &H[i]), V.emplace_back(H[i]);
	sort(V.begin(), V.end());
	V.erase(unique(V.begin(), V.end()), V.end());
	int R = 0;
	for(int i = 1; i <= n; i++) {
		while(R < n && A[R+1]-A[i] <= h) update(get(H[++R]), 1);
		ans = max(ans, query(get(H[i]+l)) - query(get(H[i])-1));
		update(get(H[i]), -1);
	}
	printf("%d\n", ans);

	return 0;
}
