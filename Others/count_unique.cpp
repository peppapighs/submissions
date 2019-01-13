#include <bits/stdc++.h>

#define ii pair<int,int>

using namespace std;

const int N = 1<<21;

long long tree[N<<1],ans[N];
int n,q,arr[N],pos[N];
vector<vector<ii> > que(N);

void update(int x,long long k,int p = 1,int l = 1,int r = n) {
	if(l == r) return void(tree[p] = k);
	int mid = (l + r) >> 1;
	if(x <= mid) update(x,k,p<<1,l,mid);
	else update(x,k,p<<1|1,mid+1,r);
	tree[p] = tree[p<<1] + tree[p<<1|1];
}

long long query(int x,int y,int p = 1,int l = 1,int r = n) {
	if(x > r || l > y) return 0LL;
	if(x <= l && r <= y) return tree[p];
	int mid = (l + r) >> 1;
	return query(x,y,p<<1,l,mid) + query(x,y,p<<1|1,mid+1,r);
}

int main() {
	scanf("%d%d",&n,&q);
	for(int i = 1;i <= n;i++) scanf("%d",&arr[i]);
	for(int i = 1,a,b;i <= q;i++) {
		scanf("%d%d",&a,&b);
		que[b].emplace_back(a,i);
	}
	for(int i = 1;i <= n;i++) {
		if(pos[arr[i]]) update(pos[arr[i]],0LL);
		update(i,1LL);
		pos[arr[i]] = i;
		for(ii ask : que[i]) ans[ask.second] = query(ask.first,i);
	}

	for(int i = 1;i <= q;i++) printf("%lld\n",ans[i]);

	return 0;
}