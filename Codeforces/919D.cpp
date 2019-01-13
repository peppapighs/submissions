#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,m;
    string s;
    scanf("%d%d",&n,&m);
    cin >> s;
    vector<int> graph[n];
    int d[n] = {0};
    while(m--) {
        int u,v;
        scanf("%d%d",&u,&v);
        graph[u-1].push_back(v-1);
        d[v-1]++;
    }

    int dp[n][26];
    for(int i=0;i<n;i++) {
        for(int j=0;j<26;j++) {
            if(s[i]-'a'==j&&!d[i]) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = 0;
            }
        }
    }
    queue<int> q;
    for(int i=0;i<n;i++) {
        q.push(i);
    }
    while(!q.empty()) {
        int u = q.front();
        printf("%d\n",u);
        q.pop();
        for(int i=0;i<graph[u].size();i++) {
            int v = graph[u][i];
            for(int j=0;j<26;j++) {
                dp[v][j] = max(dp[v][j],dp[u][j]+(s[v]-'a'==j));
                if(dp[v][j]>300000) {
                    return 0;
                }
                q.push(v);
            }
        }
    }

    int ans = 0;
    for(int i=0;i<n;i++) {
        for(int j=0;j<26;j++) {
            ans = max(ans,dp[i][j]);
        }
    }

    printf("%d",ans);

    return 0;
}
