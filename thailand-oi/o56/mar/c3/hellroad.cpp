#include <bits/stdc++.h>

#define iii tuple<int, int, int>

using namespace std;

const int N = 1e3 + 5;

int n, m;
int par[N];
vector<iii> E;

int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, a, b, c; i <= n * (n - 1) / 2; i++) {
        scanf("%d %d %d", &a, &b, &c);
        E.emplace_back(c, a, b);
    }
    sort(E.begin(), E.end());
    int l = 0, r = 1e7;
    while (l < r) {
        int mid = (l + r + 1) >> 1, cnt = 0, cost = 0;
        iota(par, par + N, 0);
        for (iii e : E) {
            int a, b, c;
            tie(c, a, b) = e;
            if (c < mid)
                continue;
            if (find(a) != find(b)) {
                par[find(a)] = find(b);
                ++cnt, cost += c;
            }
        }
        if (cnt == n - 1 && cost <= m)
            l = mid;
        else
            r = mid - 1;
    }
    printf("%d\n", l);

    return 0;
}
