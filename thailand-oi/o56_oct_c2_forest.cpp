#include <bits/stdc++.h>

#define pii pair<int ,int>
#define x first
#define y second

using namespace std;

int n, p, k;
int cost[25][25], dp[25][25][25];
vector<pii> warp[25][25];
int dx[4] = {0, 1, 0, -1}; 
int	dy[4] = {1, 0, -1, 0};

struct node {
	int d, x, y, w;
	node(int d, int x, int y, int w) : d(d), x(x), y(y), w(w) {}
	friend bool operator<(const node &a, const node &b) {
		return a.d > b.d;
	}
};

priority_queue<node> Q;

int main() {
	scanf("%d%d%d", &n, &p, &k);
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) scanf("%d", &cost[i][j]);
	while(p--) {
		int x, y, a, b;
		scanf("%d%d%d%d", &x, &y, &a, &b);
		warp[x][y].emplace_back(a, b);
	}
	for(int i = 0; i < 25; i++) for(int j = 0; j < 25; j++) for(int k = 0; k < 25; k++) dp[i][j][k] = INT_MAX;
	dp[0][0][0] = 0;
	Q.emplace(0, 0, 0, 0);
	while(!Q.empty()) {
		node now = Q.top();
		Q.pop();

		int x = now.x, y = now.y, w = now.w;
		if(dp[x][y][w] != now.d) continue;
		for(int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if(dp[x][y][w] + cost[nx][ny] < dp[nx][ny][w]) {
				dp[nx][ny][w] = dp[x][y][w] + cost[nx][ny];
				Q.emplace(dp[nx][ny][w], nx, ny, w);
			}
		}

		if(w >= k) continue;
		for(pii h : warp[x][y]) if(dp[x][y][w] < dp[h.x][h.y][w + 1]) {
			dp[h.x][h.y][w + 1] = dp[x][y][w];
			Q.emplace(dp[h.x][h.y][w + 1], h.x, h.y, w + 1);
		}
	}

	int ans = INT_MAX;
	for(int i = 0; i <= k; i++) ans = min(ans, dp[n - 1][n -  1][i]);
	printf("%d", ans);

	return 0;
}