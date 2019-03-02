#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

struct query {
	int l, r;
	double avg;
	query() {}
};

int n, m, todo = 1;
int ans[N];
long long A[N], t[N][2];
query Q[N];
pii bs[N], V[N];
queue<int> P[N];

void update(int x, int k, int y) { for(int i = x; i <= n; i += i&(-i)) t[i][y] += k; }
long long query(int x, int y) {
	long long sum = 0;
	for(int i = x; i; i -= i&(-i)) sum += t[i][y];
	return sum;
}

int main() {
	scanf("%d %d", &n, &m);
	fill(begin(bs), end(bs), pii(1, n));
	for(int i = 1; i <= n; i++) scanf("%lld", A+i), V[i] = pii(A[i], i);
	for(int i = 1; i <= m; i++) scanf("%d %d %lf", &Q[i].l, &Q[i].r, &Q[i].avg);
	sort(V+1, V+n+1, greater<pii>());
	while(todo) {
		todo = 0;
		memset(t, 0, sizeof t);
		for(int i = 1; i <= m; i++) if(bs[i].x <= bs[i].y) P[(bs[i].x + bs[i].y) >> 1].emplace(i), todo++;
		for(int i = 1; i <= n; i++) {
			update(V[i].y, V[i].x, 0), update(V[i].y, 1, 1);
			while(!P[i].empty()) {
				int now = P[i].front();
				P[i].pop();
				long long sum = query(Q[now].r, 0) - query(Q[now].l-1, 0);
				long long cnt = query(Q[now].r, 1) - query(Q[now].l-1, 1);
				if(!cnt) {
					bs[now].y = i-1;
					continue;
				}
				if((double)sum/cnt >= Q[now].avg) bs[now].x = i+1, ans[now] = (int)cnt;
				else bs[now].y = i-1;
			}
		}
	}
	for(int i = 1; i <= m; i++) {
		if(ans[i]) printf("%d\n", Q[i].r-Q[i].l+1-ans[i]);
		else printf("-1\n");
	}

	return 0;
}