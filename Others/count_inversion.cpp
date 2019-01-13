#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+5;

long long n,arr[N];

int merge(int l=1,int r=n) {
	if(l==r) return 0;
	int mid=(l+r)>>1,ret=0;
	ret+=merge(l,mid);
	ret+=merge(mid+1,r);
	long long tmp[r-l+1];
	int i=l,j=mid+1,k=0;
	while(i<=mid&&j<=r) {
		if(arr[i]<=arr[j]) tmp[k++] = arr[i++];
		else tmp[k++] = arr[j++],ret+=(mid-i+1);
	}
	while(i<=mid) tmp[k++] = arr[i++];
	while(j<=r) tmp[k++] = arr[j++];
	for(i=l;i<=r;i++) arr[i] = tmp[i-l];
	return ret;
}

int main() {
	while(scanf("%lld",&n),n) {
		for(int i=1;i<=n;i++) scanf("%lld",&arr[i]);
		printf("%d\n",merge());
		//for(int i=1;i<=n;i++) printf("%d ",arr[i]);
	}
	return 0;
}