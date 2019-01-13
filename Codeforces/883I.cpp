#include <bits/stdc++.h>

using namespace std;

int n,k;

bool check(int x,int *arr) {
    int dp[n];
    dp[0] = 1;
    int l = 0,cnt = 0;
    for(int i=0;i<n;i++) {
        if(i-k+1>=0) {
            cnt += dp[i-k+1];
        }
        while(l<=i-k+1&&arr[i]-arr[l]>x) {
            cnt -= dp[l];
            l++;
        }
        dp[i+1] = cnt > 0;
    }
    return dp[n];
}

int main()
{
    scanf("%d%d",&n,&k);
    int arr[n];
    for(int i=0;i<n;i++) {
        scanf("%d",&arr[i]);
    }
    sort(arr,arr+n);
    int low = 0, high = arr[n-1] - arr[0] + 1;
    int res = 0;
    while(low<=high) {
        int mid = (low+high)/2;
        if(check(mid,arr)) {
            high = mid-1;
            res = mid;
        } else {
            low = mid+1;
        }
    }

    printf("%d",res);

    return 0;
}
