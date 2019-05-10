#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e3+5;

int n;
vector<pii> p;
set<pair<double, double> > S;
map<double, int> mp;

int main() {
    scanf("%d", &n);
    for(int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        p.emplace_back(a, b);
    }
    for(int i = 0; i < n; i++) for(int j = i+1; j < n; j++) {
        pii x = p[i], y = p[j];
        double m = x.x != y.x ? (double)(x.y - y.y) / (double)(x.x - y.x) : 1e9;
        double c = m != 1e9 ? (double)x.y - m * x.x : x.x;
        S.emplace(m, c);
    }
    long ans = 1ll * (int)S.size() * ((int)S.size() - 1) / 2;
    for(auto it : S) ++mp[it.x];
    for(auto it : mp) ans -= 1ll * it.y * (it.y - 1) / 2;
    printf("%lld\n", ans);

    return 0;
}