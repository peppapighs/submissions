#include <bits/stdc++.h>

#define long long long
#define iii tuple<long, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

long sq(int a) { return 1ll * a * a; }
long d(pii a, pii b) { return sq(a.x - b.x) + sq(a.y - b.y); }

int n, w, h, idx, par[N];
vector<pii> vec[4];
vector<iii> E;
pii cen;

int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

int main() {
    iota(par, par + N, 0);
    scanf("%d %d %d", &n, &w, &h);
    for (int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        if (a == 0)
            vec[0].emplace_back(b, i);
        else if (a == w)
            vec[2].emplace_back(b, i);
        else if (b == 0)
            vec[3].emplace_back(a, i);
        else if (b == h)
            vec[1].emplace_back(a, i);
        else
            cen = pii(a, b), idx = i;
    }
    for (int x = 0; x < 4; x++) {
        sort(vec[x].begin(), vec[x].end());
        for (int i = 1; i < (int)vec[x].size(); i++) {
            pii a = vec[x][i], b = vec[x][i - 1];
            E.emplace_back(sq(a.x - b.x), a.y, b.y);
        }
    }
    if (idx) {
        for (pii p : vec[0])
            E.emplace_back(d(cen, pii(0, p.x)), idx, p.y);
        for (pii p : vec[1])
            E.emplace_back(d(cen, pii(p.x, h)), idx, p.y);
        for (pii p : vec[2])
            E.emplace_back(d(cen, pii(w, p.x)), idx, p.y);
        for (pii p : vec[3])
            E.emplace_back(d(cen, pii(p.x, 0)), idx, p.y);
    }
    if (!vec[0].empty() && !vec[3].empty())
        E.emplace_back(d(pii(0, vec[0][0].x), pii(vec[3][0].x, 0)), vec[0][0].y,
                       vec[3][0].y);
    if (!vec[1].empty() && !vec[0].empty())
        E.emplace_back(d(pii(vec[1][0].x, h), pii(0, vec[0].back().x)),
                       vec[1][0].y, vec[0].back().y);
    if (!vec[2].empty() && !vec[1].empty())
        E.emplace_back(d(pii(w, vec[2].back().x), pii(vec[1].back().x, h)),
                       vec[2].back().y, vec[1].back().y);
    if (!vec[3].empty() && !vec[2].empty())
        E.emplace_back(d(pii(vec[3].back().x, 0), pii(w, vec[2][0].x)),
                       vec[3].back().y, vec[2][0].y);

    if (!vec[2].empty())
        for (pii a : vec[0]) {
            auto it = lower_bound(vec[2].begin(), vec[2].end(), pii(a.x, -1));
            if (it != vec[2].end()) {
                pii b = *it;
                E.emplace_back(d(pii(0, a.x), pii(w, b.x)), a.y, b.y);
            }
            if (it != vec[2].begin()) {
                pii b = *prev(it);
                E.emplace_back(d(pii(0, a.x), pii(w, b.x)), a.y, b.y);
            }
        }
    if (!vec[3].empty())
        for (pii a : vec[1]) {
            auto it = lower_bound(vec[3].begin(), vec[3].end(), pii(a.x, -1));
            if (it != vec[3].end()) {
                pii b = *it;
                E.emplace_back(d(pii(a.x, h), pii(b.x, 0)), a.y, b.y);
            }
            if (it != vec[3].begin()) {
                pii b = *prev(it);
                E.emplace_back(d(pii(a.x, h), pii(b.x, 0)), a.y, b.y);
            }
        }

    long ans = 0;
    sort(E.begin(), E.end());
    for (iii e : E) {
        int a, b;
        long c;
        tie(c, a, b) = e;
        if (find(a) != find(b)) {
            par[find(a)] = find(b);
            ans += c;
        }
    }
    printf("%lld\n", ans);

    return 0;
}