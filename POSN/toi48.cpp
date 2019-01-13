#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    k/=8;
    pair<int,int> idol[n];
    for(int i=0;i<n;i++) {
        scanf("%d",&idol[i].first);
    }
    for(int i=0;i<n;i++) {
        scanf("%d",&idol[i].second);
        idol[i].second++;
    }

    int dp[n+1][k+1];
    for(int j=0;j<=k;j++) {
        for(int i=0;i<=n;i++) {
            dp[i][j] = 0;
        }
    }

    for(int j=1;j<=k;j++) {
        for(int i=1;i<=n;i++) {
            if(idol[i-1].second>j) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = max(dp[i-1][j],dp[i-1][j-idol[i-1].second]+idol[i-1].first);
            }
        }
    }

    printf("%d",dp[n][k]);

    return 0;
}
