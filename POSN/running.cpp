#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, s, t, c, m;
    scanf("%d%d%d%d%d", &n, &s, &t, &c, &m);
    vector<pair<int, int>> graph[n];
    while (m--) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;
    int dist1[n];
    int dist2[n];
    bool visit[n];
    for (int i = 0; i < n; i++) {
        dist1[i] = INT_MAX;
        dist2[i] = INT_MAX;
        visit[i] = false;
    }
    dist1[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        visit[u] = true;

        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i].first;
            int w = graph[u][i].second;
            if (dist1[u] + w < dist1[v] && !visit[v]) {
                dist1[v] = dist1[u] + w;
                pq.push({dist1[v], v});
            }
        }
    }
    for (int i = 0; i < n; i++) {
        visit[i] = false;
    }
    dist2[t] = 0;
    pq.push({0, t});
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        visit[u] = true;

        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i].first;
            int w = graph[u][i].second;
            if (dist2[u] + w < dist2[v] && !visit[v]) {
                dist2[v] = dist2[u] + w;
                pq.push({dist2[v], v});
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (dist1[i] + dist2[i] > c) {
            printf("%d ", i);
        }
    }

    return 0;
}
