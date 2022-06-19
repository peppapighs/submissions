#include <bits/stdc++.h>

using namespace std;

int n, m, s, d, p;

void dfs(int c, vector<pair<int, int>> graph[], int k) {
    if (c == d) {
        if (p % k == 0) {
            printf("%d", p / k);
        } else {
            printf("%d", (p / k) + 1);
        }
    } else {
        for (int i = 0; i < graph[c].size(); i++) {
            dfs(graph[c][i].second, graph, min(k, graph[c][i].first));
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);

    vector<pair<int, int>> init_graph[n], graph[n];

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        init_graph[u - 1].push_back({w - 1, v - 1});
        init_graph[v - 1].push_back({w - 1, u - 1});
    }
    scanf("%d %d %d", &s, &d, &p);
    d--;

    priority_queue<pair<int, pair<int, int>>> pq;
    int key[n] = {0};
    bool mstSet[n] = {false};
    pair<int, int> parent[n];

    parent[s - 1] = {-1, -1};
    pq.push({0, {0, s - 1}});

    while (!pq.empty()) {
        int u = pq.top().second.second;
        pq.pop();

        mstSet[u] = true;

        for (int i = 0; i < init_graph[u].size(); i++) {
            int w = init_graph[u][i].first;
            int v = init_graph[u][i].second;
            if (key[v] < w && !mstSet[v]) {
                key[v] = w;
                pq.push({key[v], {u, v}});
                parent[v] = {u, w};
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (parent[i].first != -1) {
            graph[parent[i].first].push_back({parent[i].second, i});
        }
    }

    dfs(s - 1, graph, 2e9);

    return 0;
}
