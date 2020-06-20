#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int m, n, k, cnt[N];
vector<long> coord[N], pref[N];
set<pii> S;

long get_cost(int i, long c) {
    int idx = lower_bound(coord[i].begin(), coord[i].end(), c) - coord[i].begin();
    if(idx != coord[i].size()) return pref[i][idx];
    else return 0;
}

int main() {
    scanf("%d %d %d", &m, &n, &k);
    for(int i = 1, l; i <= n; i++) {
        scanf("%d", &l);
        for(int j = 1, a, b; j <= l; j++) {
            scanf("%d %d", &a, &b);
            coord[i].emplace_back(a);
            pref[i].emplace_back(b);
        }
        for(int j = l - 2; ~j; j--) pref[i][j] += pref[i][j + 1];
    }
    for(int i = 1; i <= n; i++) S.emplace(get_cost(i, 1), i);

    long ans = 0;
    for(int i = 1; i <= m; i++) {
        pii now = *S.rbegin();
        S.erase(now);
        ans += now.x, ++cnt[now.y];
        S.emplace(get_cost(now.y, cnt[now.y] + 1), now.y);
    }
    printf("%f\n", 1.0 * ans / k);

    return 0;
}