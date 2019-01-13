#include <bits/stdc++.h>

using namespace std;

map<int,int> m;
int n;

int main() {
	scanf("%d",&n);
	int arr[n];
	for(int i=0;i<n;i++) {
		scanf("%d",&arr[i]);
	}
	int mx=0,idx;
	for(int i=0;i<n;i++) {
		m[arr[i]] = m[arr[i]-1]+1;
		if(m[arr[i]]>mx) {
            mx=m[arr[i]];
            idx=arr[i];
		}
	}
	printf("%d\n",mx);
	vector<int> ans;
	for(int i=n-1;i>=0;i--) {
		if(arr[i]==idx) {
            ans.push_back(i+1);
            idx--;
		}
	}

	for(int i=mx-1;i>=0;i--) {
        printf("%d ",ans[i]);
	}

	return 0;
}
