#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+5;

map<int,int> comp;
vector<int> idx[N];
int n,q,ptr=1;

int que(int k,int x) {
	int l=0,r=idx[comp[x]].size();
	int ret=0;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(idx[comp[x]][mid]<=k) {
			ret = mid;
			l=mid+1;
		} else {
			r=mid-1;
		}
	}
	return ret;
}

int main() {
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) {
		int a;
		scanf("%d",&a);
		if(comp.find(a)==comp.end()) {
			comp[a]=ptr++;
		}
		idx[comp[a]].emplace_back(i);
	}
	while(q--) {
		int l,r,x;
		scanf("%d%d%d",&l,&r,&x);
		int a=que(l,x),b=que(r,x);
		printf("%d\n",b-a+1);
	}

	return 0;
}