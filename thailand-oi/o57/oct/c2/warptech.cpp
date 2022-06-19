#include <bits/stdc++.h>

using namespace std;

const int N = 5e3 + 5;

struct edge {
    int u, v, w;
    edge(int u, int v, int w) : u(u), v(v), w(w) {}
    friend bool operator<(const edge &a, const edge &b) { return a.w < b.w; }
};

int n, m, q;
int par[N];
vector<int> mst;
vector<edge> E;

int find(int i) { return par[i] = par[i] == i ? i : find(par[i]); }

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 0; i < n; i++)
        par[i] = i;
    while (m--) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        E.emplace_back(u, v, w);
    }
    sort(E.begin(), E.end());
    for (edge &e : E) {
        int pu = find(e.u), pv = find(e.v);
        if (pu != pv) {
            par[pu] = pv;
            mst.emplace_back(e.w);
        }
        if (mst.size() == n - 1)
            break;
    }
    reverse(mst.begin(), mst.end());
    while (q--) {
        int a;
        scanf("%d", &a);
        printf("%d\n", mst[a - 1]);
    }

    return 0;
}
