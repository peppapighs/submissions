#include <bits/stdc++.h>

using namespace std;

const int N = 1<<18;

long long tree[N<<1],lz[N<<1];
int n,m;
long long arr[200005];

void pushlz(int rt,int l,int r) {
	if(lz[rt]) {
		tree[rt]+=lz[rt];
		if(l!=r) {
			lz[rt<<1]+=lz[rt];
			lz[rt<<1|1]+=lz[rt];
		}
	}
	lz[rt] = 0;
}

void build(int rt=1,int l=1,int r=n) {
	if(l==r) {
		tree[rt] = arr[l];
		return;
	}
	int mid = (l+r)>>1;
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
	tree[rt] = min(tree[rt<<1],tree[rt<<1|1]);
}

void update(long long k,int x,int y,int rt=1,int l=1,int r=n) {
	pushlz(rt,l,r);
	if(x>r||l>y) return;
	if(x<=l&&r<=y) {
		lz[rt]+=k;
		pushlz(rt,l,r);
		return;
	}
	int mid=(l+r)>>1;
	update(k,x,y,rt<<1,l,mid);
	update(k,x,y,rt<<1|1,mid+1,r);
	tree[rt] = min(tree[rt<<1],tree[rt<<1|1]);
}

long long query(int x,int y,int rt=1,int l=1,int r=n) {
	pushlz(rt,l,r);
	if(x>r||l>y) return LLONG_MAX;
	if(x<=l&&r<=y) return tree[rt];
	int mid=(l+r)>>1;
	return min(query(x,y,rt<<1,l,mid),query(x,y,rt<<1|1,mid+1,r));
}

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&arr[i]);
	build();
	scanf("%d",&m);
	while(m--) {
		int l,r;
		scanf("%d%d",&l,&r);
		char c;
		c = getchar();
		if(c==' ') {
			long long k;
			scanf("%lld",&k);
			if(l<=r) update(k,++l,++r);
			else update(k,1,++r),update(k,++l,n);
		} else {
			if(l<=r) printf("%lld\n",query(++l,++r));
			else printf("%lld\n",min(query(1,++r),query(++l,n)));
		}
	}

	return 0;
}