#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e6 + 5;

int n, a[N], sz[N];
long m;
deque<int> Q;

int main() {
    scanf("%d %lld", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    long sum = 0, ans = 0;
    for (int i = n, r = n; i; i--) {
        sz[i] = 1;
        while (!Q.empty() && a[Q.front()] <= a[i]) {
            int now = Q.front();
            Q.pop_front();
            sz[i] += sz[now];
            sum += 1ll * sz[now] * (a[i] - a[now]);
        }
        Q.emplace_front(i);
        while (sum > m) {
            --sz[Q.back()];
            sum -= a[Q.back()] - a[r];
            if (r == Q.back())
                Q.pop_back();
            --r;
        }
        ans += r - i + 1;
    }
    printf("%lld\n", ans);

    return 0;
}