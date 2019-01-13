#include <bits/stdc++.h>

using namespace std;

int dijkstra(vector<pair<pair<int,int>,int> > graph[],int s,int n) {
    int dist[n];
    int inset[n];
    for(int i=0;i<n;i++) {
        dist[i] = 2e9;
        inset[i] = false;
    }
    dist[0] = 0;
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pq;
    pq.push({0,0});

    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inset[u] = true;

        for(vector<pair<pair<int,int>,int> >::iterator it = graph[u].begin();it!=graph[u].end();it++) {
            int v = (*it).second;
            int w = (*it).first.second;
            int d = (*it).first.first;
            if(dist[u]+w<dist[v]&&!inset[v]&&s>=d) {
                dist[v] = dist[u]+w;
                pq.push({dist[v],v});
            }
        }
    }
    return dist[n-1];
}

int main()
{
    int n,m,k,t;
    scanf("%d %d %d %d",&n,&m,&k,&t);
    vector<pair<pair<int,int>,int> > graph[n];
    pair<int,int> shoes[k];

    for(int i=0;i<m;i++) {
        int u,v,d,t;
        scanf("%d %d %d %d",&u,&v,&d,&t);
        graph[u-1].push_back({{d,t},v-1});
        graph[v-1].push_back({{d,t},u-1});
    }

    for(int i=0;i<k;i++) {
        int p,s;
        scanf("%d %d",&p,&s);
        shoes[i] = {s,p};
    }

    sort(shoes,shoes+k);

    int low = 0,high = k-1;
    int min_s = 2e9;
    while(high>=low) {
        int mid = (low+high)/2;
        int res = dijkstra(graph, shoes[mid].first, n);

        if(res<=t) {
            high = mid-1;
            min_s = shoes[mid].first;
        } else {
            low = mid+1;
        }
    }

    if(min_s == 2e9) {
        printf("-1");
        return 0;
    }

    int min_price = 2e9;

    for(int i=0;i<k;i++) {
        if(shoes[i].first>=min_s&&shoes[i].second<min_price) {
            min_price = shoes[i].second;
        }
    }

    if(min_price == 2e9) {
        printf("-1");
        return 0;
    } else {
        printf("%d",min_price);
    }

    return 0;
}
