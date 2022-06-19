#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

int n, m, A[N], pos[N], res[N], par[N];
vector<pii> E;

int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

int main() {
    iota(par, par + N, 0);
    scanf("%d %d", &n, &m);
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        E.emplace_back(a, b);
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i), pos[A[i]] = i;
    sort(E.begin(), E.end(), [&](const pii &a, const pii &b) {
        int x = min(pos[a.x], pos[a.y]), y = min(pos[b.x], pos[b.y]);
        return x < y;
    });
    for (int i = n, c = 1; i; i--, c++) {
        while (!E.empty() && min(pos[E.back().x], pos[E.back().y]) == i) {
            int a = E.back().x, b = E.back().y;
            E.pop_back();
            if (pos[a] > pos[b])
                swap(a, b);
            int pa = find(a), pb = find(b);
            if (pa != pb) {
                par[pa] = pb;
                c--;
            }
        }
        res[i] = (c <= 1);
    }
    for (int i = 1; i <= n; i++) {
        if (res[i])
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}