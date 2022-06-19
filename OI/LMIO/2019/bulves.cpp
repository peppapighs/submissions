#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 5e5 + 5;

int n;
long a[N], b[N], c[N], ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", a + i, b + i);
        c[i] = c[i - 1] + a[i] - b[i];
    }
    priority_queue<long> Q;
    for (int i = 1; i <= n; i++) {
        if (c[i] > c[n])
            ans += c[i] - c[n], c[i] = c[n];
        else if (c[i] < 0)
            ans -= c[i], c[i] = 0;
        Q.emplace(c[i]);
        if (c[i] < Q.top()) {
            ans += Q.top() - c[i];
            Q.pop(), Q.emplace(c[i]);
        }
    }
    printf("%lld\n", ans);

    return 0;
}