#include <bits/stdc++.h>

#define pii pair<int, int>

using namespace std;

struct node {
    int d, n, o;
    node(int d, int n, int o) : d(d), n(n), o(o) {}
    friend bool operator<(const node &a, const node &b) { return a.d > b.d; }
};

const int N = 1e5 + 5;

int n, m, s, t, weight;
vector<vector<pii>> g(N);
int dist[N][2];
priority_queue<node> pq;

int main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    while (m--) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
        weight += w;
    }
    for (int i = 0; i < n; i++) {
        dist[i][0] = dist[i][1] = INT_MAX;
    }
    pq.emplace(0, s, 0);
    dist[s][0] = 0;
    while (!pq.empty()) {
        node u = pq.top();
        pq.pop();

        for (pii v : g[u.n]) {
            if (dist[u.n][u.o] + v.second < dist[v.first][u.o]) {
                dist[v.first][u.o] = dist[u.n][u.o] + v.second;
                pq.emplace(dist[v.first][u.o], v.first, u.o);
            }
            if (!u.o && dist[u.n][0] < dist[v.first][1]) {
                dist[v.first][1] = dist[u.n][0];
                pq.emplace(dist[v.first][1], v.first, 1);
            }
        }
    }
    printf("%d", weight - dist[t][1]);

    return 0;
}