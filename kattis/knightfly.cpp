#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;
const int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
const int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};

int n, a, b, c, d;
vector<pii> coord;
map<int, vector<pii>> X, Y;
vector<int> g[N];

int f(pii x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
}

void gen_dir(pii now, int idx) {
    if (idx < 4) {
        vector<pii> &vecX = X[now.x];
        auto it = lower_bound(vecX.begin(), vecX.end(), now);
        for (int i = 0; i < dx[idx]; i++) {
            ++it;
            if (it == vecX.end())
                return;
        }
        for (int i = 0; i > dx[idx]; i--) {
            if (it == vecX.begin())
                return;
            --it;
        }
        vector<pii> &vecY = Y[it->y];
        it = lower_bound(vecY.begin(), vecY.end(), *it);
        for (int i = 0; i < dy[idx]; i++) {
            ++it;
            if (it == vecY.end())
                return;
        }
        for (int i = 0; i > dy[idx]; i--) {
            if (it == vecY.begin())
                return;
            --it;
        }
        g[f(now)].emplace_back(f(*it));
    } else {
        vector<pii> &vecY = Y[now.y];
        auto it = lower_bound(vecY.begin(), vecY.end(), now);
        for (int i = 0; i < dy[idx]; i++) {
            ++it;
            if (it == vecY.end())
                return;
        }
        for (int i = 0; i > dy[idx]; i--) {
            if (it == vecY.begin())
                return;
            --it;
        }
        vector<pii> &vecX = X[it->x];
        it = lower_bound(vecX.begin(), vecX.end(), *it);
        for (int i = 0; i < dx[idx]; i++) {
            ++it;
            if (it == vecX.end())
                return;
        }
        for (int i = 0; i > dx[idx]; i--) {
            if (it == vecX.begin())
                return;
            --it;
        }
        g[f(now)].emplace_back(f(*it));
    }
}

int dist[N];

int main() {
    fill_n(dist, N, 2e9);

    scanf("%d %d %d %d %d", &n, &a, &b, &c, &d);
    for (int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        coord.emplace_back(a, b);
        X[a].emplace_back(a, b);
        Y[b].emplace_back(a, b);
    }
    sort(coord.begin(), coord.end());
    for (auto &p : X)
        sort(p.y.begin(), p.y.end());
    for (auto &p : Y)
        sort(p.y.begin(), p.y.end());

    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 8; j++)
            gen_dir(coord[i - 1], j);

    queue<int> Q;

    dist[f(pii(a, b))] = 0;
    Q.emplace(f(pii(a, b)));
    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        if (coord[now - 1] == pii(c, d))
            return !printf("%d\n", dist[now]);
        for (int v : g[now])
            if (dist[v] > dist[now] + 1) {
                dist[v] = dist[now] + 1;
                Q.emplace(v);
            }
    }
    printf("-1\n");

    return 0;
}