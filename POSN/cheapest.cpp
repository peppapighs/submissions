#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,m,c,s,e;
    scanf("%d%d",&n,&m);
    int price[n];
    vector<pair<int,int> > graph[n];
    for(int i=0;i<n;i++) {
        scanf("%d",&price[i]);
    }
    while(m--) {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});
    }
    scanf("%d%d%d",&c,&s,&e);

    int dp[n][c+1]; //dp[i][j] = minimum cost at city i with fuel j
    for(int j=0;j<=c;j++) {
        for(int i=0;i<n;i++) {
            dp[i][j] = INT_MAX;
        }
    }

    priority_queue<pair<int,pair<int,int> >,vector<pair<int,pair<int,int> > >,greater<pair<int,pair<int,int> > > > pq;
    dp[s][0] = 0;
    pq.push({0,{s,0}});
    while(!pq.empty()) {
        pair<int,pair<int,int> > u = pq.top();
        pq.pop();
        int totalp = u.first;
        int pos = u.second.first;
        int fuel = u.second.second;

        if(pos == e) {
            printf("%d",totalp);
            return 0;
        }

        if(dp[pos][fuel]==totalp) {
            if(fuel>0) {
                for(int i=0;i<graph[pos].size();i++) {
                    int v = graph[pos][i].first;
                    int w = graph[pos][i].second;
                    if(fuel-w>=0&&totalp<dp[v][fuel-w]) {
                        dp[v][fuel-w] = totalp;
                        pq.push({totalp,{v,fuel-w}});
                    }
                }
            }
            if(fuel<c&&totalp+price[pos]<dp[pos][fuel+1]) {
                dp[pos][fuel+1] = totalp+price[pos];
                pq.push({dp[pos][fuel+1],{pos,fuel+1}});
            }
        }
    }

    printf("-99");

    return 0;
}
