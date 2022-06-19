#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, m;
double sl[N], yi[N], ans[N];
vector<pii> g[N];
int chk[N];

bool solve(int st) {
    queue<int> Q;

    sl[st] = 1, yi[st] = 0;
    Q.emplace(st), chk[st] = 1;

    bool fix = false;
    vector<int> vec;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        vec.emplace_back(u);
        for (pii vw : g[u]) {
            int v, c;
            tie(v, c) = vw;
            if (!chk[v]) {
                sl[v] = -sl[u], yi[v] = c - yi[u];
                Q.emplace(v), chk[v] = 1;
            } else {
                if (sl[v] + sl[u] == 0.0) {
                    if (yi[u] + yi[v] == c)
                        continue;
                    else
                        return false;
                }

                double now = (1.0 * c - yi[u] - yi[v]) / (sl[u] + sl[v]);

                if (fix && ans[st] != now)
                    return false;
                fix = true, ans[st] = now;
            }
        }
    }

    if (!fix) {
        vector<double> tmp;
        for (int u : vec)
            tmp.emplace_back(-1.0 * yi[u] * sl[u]);
        sort(tmp.begin(), tmp.end());
        ans[st] = tmp[((int)tmp.size() - 1) / 2];
    }
    for (int u : vec)
        if (u != st)
            ans[u] = sl[u] * ans[st] + yi[u];
    return true;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }
    bool valid = true;
    for (int i = 1; i <= n; i++)
        if (!chk[i])
            valid &= solve(i);

    if (!valid)
        printf("NO\n");
    else {
        printf("YES\n");
        for (int i = 1; i <= n; i++)
            printf("%f ", ans[i]);
        printf("\n");
    }

    return 0;
}