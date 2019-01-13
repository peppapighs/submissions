#include <bits/stdc++.h>

using namespace std;

int n,m;
int *arr;
int *tree;

int pow(int x,int n) {
	if(n==0) {
		return 0;
	} else if(n==1) {
		return x;
	} else {
		int y = pow(x,n/2);
		if(n&1) {
			return x*y*y;
		} else {
			return y*y;
		}
	}
}

void build(int rt,int l,int r,int f) {
	if(l==r) {
		tree[rt] = arr[l-1];
	} else {
		int mid = (l+r)/2;
		build(rt*2,l,mid,1-f);
		build(rt*2+1,mid+1,r,1-f);
		if(f) {
			tree[rt] = tree[rt*2] | tree[rt*2+1];
		} else {
			tree[rt] = tree[rt*2] ^ tree[rt*2+1];
		}
	}
}

int upd(int rt,int l,int r,int idx,int val,int f) {
	if(l==r) {
		arr[idx] = val;
		tree[rt] = val;
	} else {
		int mid = (l+r)/2;
		if(l<=idx&&idx<=mid) {
			upd(rt*2,l,mid,idx,val,1-f);
		} else {
			upd(rt*2+1,mid+1,r,idx,val,1-f);
		}
		if(f) {
			tree[rt] = tree[rt*2] | tree[rt*2+1];
		} else {
			tree[rt] = tree[rt*2] ^ tree[rt*2+1];
		}
	}
}

int main() {
	scanf("%d%d",&n,&m);
	int z = n&1;
	n = pow(2,n);
	arr = new int[n];
	for(int i=0;i<n;i++) {
		scanf("%d",&arr[i]);
	}
	
	tree = new int[(n*2)+5] {0};

	build(1,1,n,z);
	while(m--) {
		int p,b;
		scanf("%d%d",&p,&b);
		upd(1,1,n,p,b,z);
		printf("%d\n",tree[1]);
	}

	return 0;
}