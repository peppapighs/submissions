#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+5;
int cnt[N];

int main() {
	int n,k;
	scanf("%d%d",&n,&k);
	vector<int> arr;
	for(int i=0;i<n;i++) {
		int x;
		scanf("%d",&x);
		if(!cnt[x]) {
			arr.push_back(x);
		}
		cnt[x]++;
	}
	sort(arr.begin(),arr.end());
	int ans=0;
	for(int i=0;i<arr.size()-1;i++) {
		if(arr[i+1]-arr[i]<=k&&arr[i+1]!=arr[i]) {
			ans+=cnt[arr[i]];
		}
	}

	printf("%d",n-ans);

	return 0;
}