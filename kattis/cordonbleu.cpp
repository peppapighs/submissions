#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const long INF = 1e18;

class min_matching {
  private:
    int n, m;
    long C;
    vector<vector<long>> A;
    vector<long> u, v, p, way, minv;
    vector<bool> used;

  public:
    weighted_matching(int n, int m) : n(n), m(m), C(0) {
        A.assign(n + 1, vector<long>(m + 1, 0));
    }

    void assign(int i, int j, long k) { A[i][j] = k; }

    long hungarian() {
        u.assign(n + 1, 0), v.assign(m + 1, 0), p.assign(m + 1, 0),
            way.assign(m + 1, 0);
        for (int i = 1, j0; i <= n; i++) {
            p[0] = i, j0 = 0;
            minv.assign(m + 1, INF), used.assign(m + 1, false);
            do {
                used[j0] = true;
                long delta = INF, j1;
                for (int j = 1, i0 = p[j0]; j <= m; j++)
                    if (!used[j]) {
                        int cur = A[i0][j] - u[i0] - v[j];
                        if (cur < minv[j])
                            minv[j] = cur, way[j] = j0;
                        if (minv[j] < delta)
                            delta = minv[j], j1 = j;
                    }
                for (int j = 0; j <= m; j++) {
                    if (used[j])
                        u[p[j]] += delta, v[j] -= delta;
                    else
                        minv[j] -= delta;
                }
                j0 = j1;
            } while (p[j0] != 0);
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }

        return -v[0];
    }

    vector<pii> matching() {
        vector<pii> ret;
        for (int i = 1; i <= m; i++)
            ret.emplace_back(p[i], i);
        return ret;
    }
};

const int N = 2e3 + 5;

int n, m;
long ans;
pii wine[N], cour[N], rest;

long d(pii a, pii b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
        scanf("%d %d", &wine[i].x, &wine[i].y);
    for (int i = 1; i <= m; i++)
        scanf("%d %d", &cour[i].x, &cour[i].y);
    scanf("%d %d", &rest.x, &rest.y);

    for (int i = m + 1; i <= m + n - 1; i++)
        cour[i] = rest;
    m += n - 1;

    min_matching hung(n, m);
    for (int i = 1; i <= n; i++) {
        ans += d(wine[i], rest);
        for (int j = 1; j <= m; j++)
            hung.assign(i, j, d(wine[i], cour[j]));
    }
    long ret = hung.hungarian();
    printf("%lld\n", ans + ret);

    return 0;
}