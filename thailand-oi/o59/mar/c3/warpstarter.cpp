#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, k;
long ans = LLONG_MAX, sum;
vector<pii> V;
set<pii> W;
map<long, long> mp;

long d(pii a, pii b) { return abs(a.x - b.x) + abs(a.y - b.y); }

void add(pii p) {
    auto pos = W.upper_bound(p);
    if (W.empty())
        return void(W.emplace(p));
    if (pos == W.end()) {
        --pos;
        mp[p.x] = d(p, *pos);
        sum += mp[p.x];
    } else if (pos == W.begin()) {
        mp[pos->x] = d(*pos, p);
        sum += mp[pos->x];
    } else {
        auto pre = pos;
        --pre;
        sum -= mp[pos->x];
        mp[pos->x] = d(*pos, p);
        mp[p.x] = d(p, *pre);
        sum += mp[pos->x] + mp[p.x];
    }
    W.emplace(p);
}

void del(pii p) {
    auto pos = W.find(p);
    auto l = pos, r = pos;
    --l, ++r;
    if (pos == W.begin()) {
        sum -= mp[r->x];
        mp[r->x] = 0;
    } else if (r == W.end())
        sum -= mp[p.x];
    else {
        sum -= mp[r->x] + mp[p.x];
        mp[r->x] = d(*l, *r);
        sum += mp[r->x];
    }
    W.erase(p);
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        V.emplace_back(a, b);
    }
    sort(V.begin(), V.end(),
         [&](const pii &a, const pii &b) { return a.y < b.y; });
    for (int i = 0; i < k; i++)
        add(V[i]);
    ans = min(ans, sum);
    for (int i = k; i < n; i++) {
        del(V[i - k]), add(V[i]);
        ans = min(ans, sum);
    }
    printf("%lld\n", ans);

    return 0;
}
