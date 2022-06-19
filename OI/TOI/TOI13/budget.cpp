#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, x, y, z;
    scanf("%d %d %d %d %d", &n, &m, &x, &y, &z);
    vector<pair<int, int>> graph[n];

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u].push_back({w, v});
        graph[v].push_back({w, u});
    }

    int dist1[n], dist2[n];
    int inset1[n], inset2[n];
    for (int i = 0; i < n; i++) {
        dist1[i] = 2e9;
        dist2[i] = 2e9;
        inset1[i] = false;
        inset2[i] = false;
    }
    dist1[x] = 0;
    dist2[y] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;
    pq.push({0, x});
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inset1[u] = true;
        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i].second;
            int w = graph[u][i].first;
            if (dist1[u] + w < dist1[v] && !inset1[v]) {
                dist1[v] = dist1[u] + w;
                pq.push({dist1[v], v});
            }
        }
    }
    pq.push({0, y});
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inset2[u] = true;
        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i].second;
            int w = graph[u][i].first;
            if (dist2[u] + w < dist2[v] && !inset2[v]) {
                dist2[v] = dist2[u] + w;
                pq.push({dist2[v], v});
            }
        }
    }

    int node, d = 2e9;

    for (int i = 0; i < n; i++) {
        if (dist2[i] < d && dist1[i] <= z) {
            d = dist2[i];
            node = i;
        }
    }

    printf("%d %d %d", node, dist1[node], d);

    return 0;
}
