#include <bits/stdc++.h>

#define pii pair<int,int>

using namespace std;

int n,m,t,x,y;
const int N = 1e4+5;
vector<vector<pii> > g(N);
long long dp[N][8];

struct qp {
	long long d;
	int n,oe;
	qp(long long d,int n,int oe) : d(d),n(n),oe(oe) {}
	friend bool operator<(const qp &a,const qp &b) {
		return a.d>b.d;
	}
};

int main() {
	scanf("%d%d%d%d%d",&n,&m,&t,&x,&y);
	while(m--) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		g[--u].emplace_back(--v,w);
	}
	--x,--y;
	for(int i=0;i<n;i++) {
		for(int j=0;j<8;j++) {
			dp[i][j] = LLONG_MAX;
		}
	}
	priority_queue<qp> pq;
	dp[x][0] = 0;
	pq.emplace(0LL,x,0);
	while(!pq.empty()) {
		qp u = pq.top();
		pq.pop();

		for(pii z : g[u.n]) {
			int v = z.first;
			long long w = z.second;
			if(dp[u.n][u.oe]+w<dp[v][(u.oe+1)%t]) {
				dp[v][(u.oe+1)%t] = dp[u.n][u.oe]+w;
				pq.emplace(dp[v][(u.oe+1)%t],v,(u.oe+1)%t);
			}
		}
	}

	if(dp[y][t-1]==LLONG_MAX) {
		printf("-1");
	} else {
		printf("%lld",dp[y][t-1]);
	}

	return 0;
}