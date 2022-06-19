#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;

int n, m;
int par[N], sz[N];

int find(int x) { return x == par[x] ? x : find(par[x]); }

void unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b)
        return;
    if (sz[a] > sz[b])
        swap(a, b);
    sz[b] += sz[a], par[a] = b;
}

int main() {
    fill_n(sz, N, 1), iota(par, par + N, 0);
    scanf("%d %d", &n, &m);
    for (int i = 1, k; i <= m; i++) {
        scanf("%d", &k);
        for (int j = 1, a, pv = -1; j <= k; j++, pv = a) {
            scanf("%d", &a);
            if (j > 1)
                unite(a, pv);
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", sz[find(i)]);
    printf("\n");

    return 0;
}