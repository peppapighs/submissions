#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+5;

int n,arr[N];

void merge(int l=1,int r=n) {
	if(l==r) return;
	int mid=(l+r)>>1;
	merge(l,mid);
	merge(mid+1,r);
	int tmp[r-l+1];
	int i=l,j=mid+1,k=0;
	while(i<=mid&&j<=r) {
		if(arr[i]<=arr[j]) tmp[k++] = arr[i++];
		else tmp[k++] = arr[j++];
	}
	while(i<=mid) tmp[k++] = arr[i++];
	while(j<=r) tmp[k++] = arr[j++];
	for(i=l;i<=r;i++) arr[i] = tmp[i-l];
}

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&arr[i]);
	merge();
	for(int i=1;i<=n;i++) printf("%d ",arr[i]);

	return 0;
}