#include <bits/stdc++.h>

using namespace std;

const long long MAX = 1e5+5;
long long arr[MAX];
long long dp[MAX];

int main(){
	long long n,w,k;
	scanf("%lld%lld%lld",&n,&w,&k);
	for(long long i = 1;i<=n;++i){
		scanf("%lld",&arr[i]);
	}
	long long l = 1,r = 1e18;
	long long ans = 0;
	while(l<=r){
		long long mid = (l+r)/2;
		long long cnt = 0;
		memset(dp,0,sizeof dp);
		for(long long i = 1;i<=n;++i){
			dp[i]+=dp[i-1];
			if(arr[i]>mid){
				long long c = arr[i]-mid;
				if(c>dp[i]){
					cnt+=c-dp[i];
					dp[i+w]-=c-dp[i];
					dp[i] = c;
				}
			}
		}
		if(cnt>k){
			l = mid+1;
		}else{
			ans = mid;
			r = mid-1;
		}
	}
	printf("%lld\n",ans);
}