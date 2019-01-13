#include <bits/stdc++.h>

using namespace std;

const int N = 1<<18;

int tree[N<<1],arr[N];
int n,m,ptr;
map<int,int> comp;
vector<int> loc[N];

void build(int p = 1,int l = 1,int r = n) {
	if(l == r) {
		tree[p] = arr[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
	tree[p] = __gcd(tree[p<<1],tree[p<<1|1]);
}

int query(int x,int y,int p = 1,int l = 1,int r = n) {
	if(x > r || l > y) return 0;
	if(x <= l && r <= y) return tree[p];
	int mid = (l + r) >> 1;
	return __gcd(query(x,y,p<<1,l,mid),query(x,y,p<<1|1,mid+1,r));
	
}

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d",&arr[i]);
		if(comp.find(arr[i]) == comp.end()) comp[arr[i]] = ptr++;
		loc[comp[arr[i]]].emplace_back(i);
	}
	build();
	scanf("%d",&m);
	while(m--) {
		int a,b;
		scanf("%d%d",&a,&b);
		int gcd = query(a,b);
		if(comp.find(gcd) == comp.end()) printf("%d\n",b-a+1);
		else {
			int cnt = upper_bound(loc[comp[gcd]].begin(),loc[comp[gcd]].end(),b)-lower_bound(loc[comp[gcd]].begin(),loc[comp[gcd]].end(),a);
			printf("%d\n",b-a+1-cnt);
		}
		//printf("%d\n",gcd);
	}

	return 0;
}