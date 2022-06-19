#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 3e4 + 5;
const int M = 2e3 + 5;

int n, m, st, en;
int d[N], chk[N][M];
vector<int> B[N];

int main() {
    fill_n(d, N, 1e9);
    scanf("%d %d", &n, &m);
    for (int i = 0, b, p; i < m; i++) {
        scanf("%d %d", &b, &p);
        B[b].emplace_back(p);
        if (i == 0)
            st = b;
        if (i == 1)
            en = b;
    }
    for (int i = 0; i < n; i++) {
        sort(B[i].begin(), B[i].end());
        B[i].resize(unique(B[i].begin(), B[i].end()) - B[i].begin());
    }
    priority_queue<pii, vector<pii>, greater<pii>> Q;
    Q.emplace(d[st] = 0, st);
    while (!Q.empty()) {
        pii now = Q.top();
        Q.pop();
        if (d[now.y] != now.x)
            continue;
        int u = now.y;
        for (int p : B[u]) {
            for (int i = u + p, cnt = 1; i < n; i += p, cnt++) {
                if (p < M && chk[i][p])
                    break;
                if (d[i] > d[u] + cnt) {
                    Q.emplace(d[i] = d[u] + cnt, i);
                    if (p < M)
                        chk[i][p] = true;
                }
            }
            for (int i = u - p, cnt = 1; i >= 0; i -= p, cnt++) {
                if (p < M && chk[i][p])
                    break;
                if (d[i] > d[u] + cnt) {
                    Q.emplace(d[i] = d[u] + cnt, i);
                    if (p < M)
                        chk[i][p] = true;
                }
            }
        }
    }
    if (d[en] != 1e9)
        printf("%d\n", d[en]);
    else
        printf("-1\n");

    return 0;
}