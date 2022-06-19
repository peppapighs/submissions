#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int f, e;
int R[105], M[105], dist[N];
vector<int> coord, g[N];

int get(int x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin();
}

void solve() {
    fill_n(dist, N, 2e9);

    scanf("%d %d", &f, &e);

    coord.emplace_back(0), coord.emplace_back(f - 1);
    for (int i = 0; i < e; i++) {
        scanf("%d %d", R + i, M + i);
        for (int j = R[i]; j < f; j += M[i])
            coord.emplace_back(j);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    for (int i = 0; i < e; i++)
        for (int j = R[i]; j < f; j += M[i])
            if (j + M[i] < f) {
                g[get(j)].emplace_back(get(j + M[i]));
                g[get(j + M[i])].emplace_back(get(j));
            }

    priority_queue<pii, vector<pii>, greater<pii>> Q;

    Q.emplace(dist[get(0)] = 0, get(0));
    while (!Q.empty()) {
        pii now = Q.top();
        Q.pop();

        int d, u;
        tie(d, u) = now;
        if (dist[u] != d)
            continue;

        for (int v : g[u])
            if (dist[v] > d)
                Q.emplace(dist[v] = d, v);
        if (u > 0 && dist[u - 1] > d + coord[u] - coord[u - 1])
            Q.emplace(dist[u - 1] = d + coord[u] - coord[u - 1], u - 1);
        if (u < coord.size() - 1 && dist[u + 1] > d + coord[u + 1] - coord[u])
            Q.emplace(dist[u + 1] = d + coord[u + 1] - coord[u], u + 1);
    }

    int ans = 0, u = 0;
    for (int i = 0; i < coord.size() - 1; i++)
        for (int d : {-1, 0, 1}) {
            int pos =
                ((-dist[i] + dist[i + 1] + coord[i] + coord[i + 1]) / 2) + d;
            if (pos < coord[i] || coord[i + 1] < pos)
                continue;
            int ret =
                min(pos - coord[i] + dist[i], coord[i + 1] - pos + dist[i + 1]);
            if (ans < ret)
                ans = ret, u = pos;
        }
    printf("%d %d\n", ans, u);

    coord.clear();
    for (int i = 0; i < N; i++)
        g[i].clear();
}

int T;

int main() {
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}