#include <bits/stdc++.h>

using namespace std;

int main() {
	int n,m,sum=0;
	scanf("%d%d",&n,&m);
	int arr[n];
	for(int i=0;i<n;i++) {
		scanf("%d",&arr[i]);
		sum+=arr[i];
	}
	
	int l=0,r=sum;
	int res=sum;
	while(l<=r) {
		int mid = (l+r)>>1;
		int s=0,p=1;
		for(int i=0;i<n;i++) {
			if(arr[i]>mid) {
				p=2e9;
				break;
			}
			if(s+arr[i]>mid) {
				p++;
				s=arr[i];
			} else {
				s+=arr[i];
			}
		}
		if(p<=m) {
			r=mid-1;
			res=mid;
		} else {
			l=mid+1;
		}
	}
	
	printf("%d",res);
	
	return 0;
}