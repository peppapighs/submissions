#include <bits/stdc++.h>

#define pii pair<int,int>

using namespace std;

const int N = 5e4+5;

int n,m,p,ptr;
int color[N];
bool vis[N];
vector<vector<pii> > g(N);
pii que[N];

void dfs(int u,int k) {
	color[u]=ptr;
	vis[u]=true;
	for(pii v : g[u]) if(v.second<k&&!vis[v.first]) dfs(v.first,k);
}

int main() {
	scanf("%d%d%d",&n,&m,&p);
	while(m--) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		g[--u].emplace_back(--v,w);
		g[v].emplace_back(u,w);
	}
	for(int i=0;i<p;i++) {
		int a,b;
		scanf("%d%d",&a,&b);
		que[i] = {--a,--b};
	}
	int l=1,r=1e9+1;
	int res=0;
	while(l<=r) {
		int mid=(l+r)>>1;
		ptr=1;
		memset(vis,false,N);
		for(int i=0;i<n;i++) {
			if(!vis[i]) {
				dfs(i,mid);
				ptr++;
			}
		}

		bool ans=true;
		for(int i=0;i<p;i++) {
			if(color[que[i].first]==color[que[i].second]) {
				ans = false;
				break;
			}
		}
		if(ans) {
			res = mid;
			l=mid+1;
		} else {
			r=mid-1;
		}
	}
	if(res!=1e9+1) printf("%d",res);
	else printf("-1");

	return 0;
}