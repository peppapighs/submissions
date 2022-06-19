#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

long labs(long a) { return a < 0 ? -a : a; }

long dist(pii a, pii b) {
    long diag = labs(a.y - b.y);
    long hori = labs(a.x - b.x);
    if (diag <= hori)
        return hori;
    else
        return diag + ((diag & 1) ^ (hori & 1));
}

int m, q;
map<pii, vector<pii>> mp;
vector<pii> coord;

int get(pii x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin();
}

long ap[205][205];

int main() {
    scanf("%d %d", &m, &q);
    for (long i = 1; i <= m; i++) {
        long a, b, c, d;
        scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
        mp[pii(a, b)].emplace_back(c, d);
        mp[pii(c, d)].emplace_back(a, b);
        coord.emplace_back(a, b), coord.emplace_back(c, d);
    }
    sort(coord.begin(), coord.end());
    coord.erase(unique(coord.begin(), coord.end()), coord.end());
    fill_n(ap[0], 205 * 205, 1e12);
    for (int i = 0; i < coord.size(); i++) {
        pii st = coord[i];
        for (pii x : mp[st])
            ap[i][get(x)] = 1;
    }
    for (int i = 0; i < coord.size(); i++)
        for (int j = 0; j < coord.size(); j++)
            ap[i][j] = min(ap[i][j], dist(coord[i], coord[j]));
    for (int k = 0; k < coord.size(); k++)
        for (int i = 0; i < coord.size(); i++)
            for (int j = 0; j < coord.size(); j++)
                ap[i][j] = min(ap[i][j], ap[i][k] + ap[k][j]);
    while (q--) {
        long a, b, c, d;
        scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
        long ans = dist(pii(a, b), pii(c, d));
        for (int i = 0; i < coord.size(); i++)
            for (int j = 0; j < coord.size(); j++)
                ans = min(ans, dist(pii(a, b), coord[i]) + ap[i][j] +
                                   dist(coord[j], pii(c, d)));
        printf("%lld\n", ans);
    }

    return 0;
}