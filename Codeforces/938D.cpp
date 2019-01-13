#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    vector<pair<long long,int> > graph[n];
    set<pair<long long,int> > pq;
    long long dist[n];

    for(int i=0;i<m;i++) {
        int u,v;
        long long w;
        scanf("%d %d %lld",&u,&v,&w);
        graph[u-1].push_back({w*2,v-1});
        graph[v-1].push_back({w*2,u-1});
    }

    for(int i=0;i<n;i++) {
        scanf("%lld",&dist[i]);
        pq.insert({dist[i],i});
    }

    while(!pq.empty()) {
        int u = pq.begin()->second;
        pq.erase(pq.begin());

        for(vector<pair<long long,int> >::iterator it = graph[u].begin();it!=graph[u].end();it++) {
            int v = it->second;
            long long w = it->first;

            if(dist[u]+w<dist[v]) {
                pq.erase({dist[v], v});
                dist[v] = dist[u] + w;
                pq.insert({dist[v],v});
            }
        }
    }

    for(int i=0;i<n;i++) {
        printf("%lld ",dist[i]);
    }

    return 0;
}
