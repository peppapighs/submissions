#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

long dist(pii a, pii b) { return abs(a.x - b.x) + abs(a.y - b.y); }

int k, m;
long ap[65][65];
vector<pii> coord;
map<pii, vector<pii> > mp;

int get(pii x) { return lower_bound(coord.begin(), coord.end(), x) - coord.begin(); }

int main() {
    fill_n(ap[0], 65*65, 1e12);
    scanf("%d %d", &k, &m);
    for(int i = 1; i <= k; i++) {
        long a, b, c, d;
        scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
        mp[pii(a, b)].emplace_back(c, d);
        mp[pii(c, d)].emplace_back(a, b);
        coord.emplace_back(a, b), coord.emplace_back(c, d);
    }
    sort(coord.begin(), coord.end());
    coord.erase(unique(coord.begin(), coord.end()), coord.end());
    for(int i = 0; i < coord.size(); i++) {
        ap[i][i] = 0;
        pii now = coord[i];
        for(pii nex : mp[now]) ap[i][get(nex)] = 0;
    } 
    for(int i = 0; i < coord.size(); i++)
        for(int j = 0; j < coord.size(); j++)
            ap[i][j] = min(ap[i][j], dist(coord[i], coord[j]));
    for(int k = 0; k < coord.size(); k++)
        for(int i = 0; i < coord.size(); i++)
            for(int j = 0; j < coord.size(); j++)
                ap[i][j] = min(ap[i][j], ap[i][k] + ap[k][j]);
    while(m--) {
        long a, b, c, d;
        scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
        long ans = dist(pii(a, b), pii(c, d));
        for(int i = 0; i < coord.size(); i++)
            for(int j = 0; j < coord.size(); j++)
                ans = min(ans, dist(pii(a, b), coord[i]) + ap[i][j] + dist(coord[j], pii(c, d)));
        printf("%lld\n", ans);
    }

    return 0;
}