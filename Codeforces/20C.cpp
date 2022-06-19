#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<pair<int, long long>> graph[n];

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        scanf("%d %d %lld", &u, &v, &w);
        graph[u - 1].push_back({v - 1, w});
        graph[v - 1].push_back({u - 1, w});
    }

    long long dist[n];
    bool inset[n];
    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>>
        pq;
    int parent[n];
    for (int i = 0; i < n; i++) {
        dist[i] = LONG_LONG_MAX;
        parent[i] = -1;
        inset[i] = false;
    }
    dist[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inset[u] = true;

        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i].first;
            long long w = graph[u][i].second;

            if (dist[u] + w < dist[v] && !inset[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
                parent[v] = u;
            }
        }
    }

    if (dist[n - 1] == LONG_LONG_MAX) {
        printf("-1");
        return 0;
    }

    deque<int> q;
    int i = n - 1;
    while (i != 0) {
        q.push_front(i);
        i = parent[i];
    }

    printf("1 ");

    for (int i = 0; i < q.size(); i++) {
        printf("%d ", q[i] + 1);
    }

    return 0;
}
