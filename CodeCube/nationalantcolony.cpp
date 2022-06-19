#include <bits/stdc++.h>

#define iii tuple<int, int, int>

using namespace std;

const int N = 5e4 + 5;

int par[N];

void init() { iota(par, par + N, 0); }

int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

int n, m, k;
vector<iii> E, mst;
vector<vector<int>> species;

int main() {
    init();

    scanf("%d %d %d", &n, &m, &k);
    species = vector<vector<int>>(k + 1);

    for (int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        species[a].emplace_back(i);
    }

    for (int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        E.emplace_back(c, a, b);
    }
    sort(E.begin(), E.end(), greater<iii>());
    for (iii e : E) {
        int a, b, c;
        tie(c, a, b) = e;
        if (find(a) != find(b)) {
            mst.emplace_back(e);
            par[find(a)] = find(b);
        }
    }

    int l = 0, r = 1e9 + 1;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        bool valid = true;

        init();
        for (iii e : mst) {
            int a, b, c;
            tie(c, a, b) = e;
            if (c > mid)
                par[find(a)] = find(b);
        }
        for (vector<int> &vec : species) {
            for (int i = 1; i < vec.size(); i++)
                if (find(vec[i]) != find(vec[i - 1])) {
                    valid = false;
                    break;
                }
            if (!valid)
                break;
        }
        if (valid)
            l = mid;
        else
            r = mid - 1;
    }
    int ans = 0;
    for (iii e : E)
        if (get<0>(e) <= l)
            ++ans;
    printf("%d\n", ans);

    return 0;
}