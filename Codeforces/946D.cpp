#include <bits/stdc++.h>

using namespace std;

int mn[501][501],dp[501][501];

int main()
{
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    vector<int> pos[n];
    for(int i=0;i<n;i++) {
        string s;
        cin >> s;
        for(int j=0;j<m;j++) {
            if(s[j]=='1') {
                pos[i].push_back(j);
            }
        }
    }

    for(int i=1;i<=n;i++) {
        int t = pos[i-1].size();
        if(t==0) continue;
        for(int l=1;l<=t;l++) {
            mn[i][t-l] = pos[i-1][l-1]-pos[i-1][0]+1;
            for(int j=0;j<t-l+1;j++) {
                mn[i][t-l] = min(mn[i][t-l],pos[i-1][j+l-1]-pos[i-1][j]+1);
            }
        }
    }

    for(int i=0;i<=k;i++) {
        dp[1][i]=mn[1][i];
    }
    for(int i=2;i<=n;i++) {
        for(int j=0;j<=k;j++) {
            dp[i][j]=dp[i-1][j]+mn[i][0];
            for(int o=0;o<=j;o++) {
                dp[i][j]=min(dp[i][j],dp[i-1][j-o]+mn[i][o]);
            }
        }
    }

    printf("%d",dp[n][k]);

    return 0;
}
