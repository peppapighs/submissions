#include <bits/stdc++.h>

using namespace std;

int n,m,s,t;

int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&t);
    s--;
    t--;
    vector<int> graph[n];
    for(int i=0;i<m;i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        graph[u-1].push_back(v-1);
        graph[v-1].push_back(u-1);
    }
    queue<int> q;
    int dist1[n];
    int dist2[n];
    for(int i=0;i<n;i++) {
        dist1[i] = dist2[i] = 1e9;
    }
    dist1[s] = 0;
    q.push(s);
    while(!q.empty()) {
        int u = q.front();
        q.pop();

        for(int i=0;i<graph[u].size();i++) {
            int v = graph[u][i];
            if(dist1[u]+1<dist1[v]) {
                dist1[v] = dist1[u]+1;
                q.push(v);
            }
        }
    }
    dist2[t] = 0;
    q.push(t);
    while(!q.empty()) {
        int u = q.front();
        q.pop();

        for(int i=0;i<graph[u].size();i++) {
            int v = graph[u][i];
            if(dist2[u]+1<dist2[v]) {
                dist2[v] = dist2[u]+1;
                q.push(v);
            }
        }
    }
    int res = 0;
    int shortest = dist1[t];
    for(int j=0;j<n;j++) {
        for(int i=j+1;i<n;i++) {
            if(dist1[i]+dist2[j]+1>=shortest&&dist1[j]+dist2[i]+1>=shortest) {
                res++;
            }
        }
    }

    printf("%d",res-m);

    return 0;
}
