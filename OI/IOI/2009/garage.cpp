#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e3 + 5;

int n, m, pos[N];
long r[N], w[N];
queue<int> Q;
priority_queue<int, vector<int>, greater<int>> PQ;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", r + i), PQ.emplace(i);
    for (int i = 1; i <= m; i++)
        scanf("%lld", w + i);

    long ans = 0;
    for (int i = 1, a; i <= 2 * m; i++) {
        scanf("%d", &a);
        if (a > 0)
            Q.emplace(a);
        else {
            int garage = pos[-a];
            PQ.emplace(garage);
        }
        while (!Q.empty() && !PQ.empty()) {
            int now = Q.front();
            Q.pop();
            int garage = PQ.top();
            PQ.pop();
            pos[now] = garage;
            ans += r[garage] * w[now];
        }
    }
    printf("%lld\n", ans);

    return 0;
}