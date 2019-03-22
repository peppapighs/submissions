#include <bits/stdc++.h>

#define ii pair<int,int>

using namespace std;

struct node {
	int d,n,lvl;
	node(int d,int n,int lvl) : d(d),n(n),lvl(lvl) {}
	friend bool operator<(const node &a,const node &b) {
		return a.d>b.d;
	}
};

const int N = 5e4+5;

int n,m,l,s,t;
vector<vector<ii> > g(N);
int dp[N][40];
int val[N];
priority_queue<node> pq;

int main() {
	scanf("%d%d%d%d%d",&n,&m,&l,&s,&t);
	--s,--t;
	for(int i=0;i<n;i++) scanf("%d",&val[i]);
	while(m--) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		g[--u].emplace_back(--v,w);
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<=l+1;j++)
			dp[i][j] = INT_MAX;
	dp[s][0]=0;
	pq.emplace(0,s,0);
	while(!pq.empty()) {
		node now = pq.top();
		pq.pop();
		//printf("%d %d %d\n",now.d,now.n,now.lvl);
		//if(now.lvl>l) continue;
		for(ii vw : g[now.n]) {
			int v = vw.first,w = vw.second,nlvl=now.lvl;
			if(now.lvl+1==val[v]) nlvl++;
			if(dp[now.n][now.lvl]+w<dp[v][nlvl]) {
				dp[v][nlvl] = dp[now.n][now.lvl]+w;
				pq.emplace(dp[v][nlvl],v,nlvl);
			}
		}
	}

	printf("%d",dp[t][l]);

	return 0;
}