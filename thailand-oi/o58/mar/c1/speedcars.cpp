#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;

int n, ans;
long T, mx = -1, x[N], v[N];
vector<int> V;

int main() {
    scanf("%d %lld", &n, &T);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", x + i, v + i);
        V.emplace_back(i);
    }
    sort(V.begin(), V.end(), [&](const int &a, const int &b) {
        if (x[a] != x[b])
            return x[a] < x[b];
        else
            return v[a] > v[b];
    });
    for (int i : V) {
        long now = x[i] + (T * v[i]);
        if (mx >= now)
            ++ans;
        mx = max(mx, now);
    }
    printf("%d\n", n - ans);

    return 0;
}