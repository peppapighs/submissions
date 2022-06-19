#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 5e4 + 5;

int n, mx[N], mn[N];
long total, ans = LLONG_MAX;
vector<pii> X = {pii(-1, -1)}, Y = {pii(-1, -1)};

void f(vector<pii> &V) {
    sort(V.begin(), V.end());
    mn[n + 1] = INT_MAX;
    for (int i = n; i; i--) {
        mx[i] = max(mx[i + 1], V[i].y);
        mn[i] = min(mn[i + 1], V[i].y);
    }
    total = 1ll * (mx[1] - mn[1]) * (V[n].x - V[1].x);
    for (int i = 1, a = 0, b = INT_MAX; i < n; i++) {
        int j = i + 1;
        a = max(a, V[i].y), b = min(b, V[i].y);
        ans = min(ans, 1ll * (a - b) * (V[i].x - V[1].x) +
                           1ll * (mx[j] - mn[j]) * (V[n].x - V[j].x));
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        X.emplace_back(a, b), Y.emplace_back(b, a);
    }
    f(X), f(Y);
    printf("%lld\n", total - ans);

    return 0;
}