#include <bits/stdc++.h>

using namespace std;

const long long INF = -2e10;

struct node {
	long long mp,ms,ts,sub; //max prefix, max suffix, total sum, max subarray
	node() : mp(INF),ms(INF),ts(INF),sub(INF) {}
	node(long long mp,long long ms,long long ts,long long sub) : mp(mp),ms(ms),ts(ts),sub(sub) {}
	friend node operator+(const node &a,const node &b) { //merge operator
		node ret;
		ret.mp = max(a.mp,a.ts+b.mp);
		ret.ms = max(b.ms,a.ms+b.ts);
		ret.ts = a.ts+b.ts;
		ret.sub = max(max(a.sub,b.sub),a.ms+b.mp);
		return ret;
	}
};

const int N = 1<<18;

node tree[N<<1];
long long arr[N];

int n,q;

void build(int rt=1,int l=1,int r=n) {
	if(l==r) {
		tree[rt] = {arr[l],arr[l],arr[l],arr[l]};
		return;
	}
	int mid = (l+r)>>1;
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
	tree[rt] = tree[rt<<1]+tree[rt<<1|1];
}

node query(int x,int y,int rt=1,int l=1,int r=n) {
	if(l>y||r<x) {
		node ret;
		return ret;
	}
	if(x<=l&&r<=y) return tree[rt];
	int mid=(l+r)>>1;
	node left = query(x,y,rt<<1,l,mid);
	node right = query(x,y,rt<<1|1,mid+1,r);
	return left+right;
}

int main() {
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%lld",&arr[i]);
	build();

	while(q--) {
		int a,b;
		scanf("%d%d",&a,&b);
		node res = query(++a,++b);
		if(res.sub<=0) printf("0\n");
		else printf("%lld\n",res.sub);
	}

	return 0;
}