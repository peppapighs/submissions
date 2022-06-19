#include <bits/stdc++.h>

#define pii pair<int, int>
#define piii pair<int, pii>

using namespace std;

const int N = 1e5 + 5;

int n, m;
int dist[N][2];

struct edge {
    int v, w, k;
    edge() {}
};

vector<vector<edge>> g(N);

priority_queue<piii, vector<piii>, greater<piii>> pq;

int dijkstra(int q) {
    for (int i = 0; i < n; i++) {
        dist[i][0] = dist[i][1] = 2e9;
    }
    dist[0][0] = 0;
    pq.push({0, {0, 0}});
    while (!pq.empty()) {
        piii k = pq.top();
        pq.pop();

        for (edge v : g[k.second.first])
            if (v.k <= q) {
                if (dist[k.second.first][k.second.second] + v.w <
                    dist[v.v][1 - k.second.second]) {
                    dist[v.v][1 - k.second.second] =
                        dist[k.second.first][k.second.second] + v.w;
                    pq.push({dist[v.v][1 - k.second.second],
                             {v.v, 1 - k.second.second}});
                }
            }
    }

    return dist[n - 1][1];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        edge e;
        int a, b;
        scanf("%d%d%d", &a, &b, &e.w);
        e.k = i;
        e.v = --b;
        g[--a].push_back(e);
        e.v = a;
        g[b].push_back(e);
    }

    int mdis = dijkstra(m);
    int l = 0, r = m - 1;
    int ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        int dis = dijkstra(mid);
        if (dis == mdis) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    printf("%d %d\n", ans + 1, mdis);

    return 0;
}