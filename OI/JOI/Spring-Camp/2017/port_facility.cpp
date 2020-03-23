#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e6+5;
const int M = 1e9+7;

int par[N << 1];

int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

int n;
vector<pii> vec;
map<int, int> mp;

int main() {
    iota(par, par + (N << 1), 0);

    scanf("%d", &n);
    for(int i = 1, x, y; i <= n; i++) {
        scanf("%d %d", &x, &y);
        vec.emplace_back(x, y);
    }
    sort(vec.begin(), vec.end());
    for(int i = 0; i < n; i++) {
        auto st = mp.lower_bound(vec[i].x), en = mp.upper_bound(vec[i].y);
        if(en != mp.begin()) for( ; st != en; st++) {
            par[find(i)] = find(st->y + n);
            par[find(i + n)] = find(st->y);
            if(find(st->y) == find(prev(en)->y)) break;
        }
        mp[vec[i].y] = i;
    }
    for(int i = 0; i < n; i++) if(find(i) == find(i + n)) return !printf("0\n");
    long ans = 1;
    for(int i = 0; i < n; i++) if(find(i) == i) ans = ans * 2 % M;
    printf("%lld\n", ans);

    return 0;
}