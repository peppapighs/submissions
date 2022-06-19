#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 3e3 + 5;

struct item {
    long cnt, idx;
    int pos;
    item(long cnt, long idx, int pos) : cnt(cnt), idx(idx), pos(pos) {}
    friend bool operator<(const item &a, const item &b) {
        return a.cnt < b.cnt;
    }
};

int n, m, k;
long A, B, C, T, ans;
long st[N], dist[N];

long get_cnt(int i, long l, long r) {
    long t = (l - st[i]) * C + dist[i];
    if (t > T)
        return 0;
    return min((T - t) / A + 1, r - l + 1);
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    scanf("%lld %lld %lld %lld", &A, &B, &C, &T);
    for (int i = 1; i <= m; i++) {
        scanf("%lld", st + i);
        if (i > 1)
            dist[i] = B * (st[i] - st[i - 1]) + dist[i - 1];
    }
    if (dist[m] <= T)
        ++ans;
    priority_queue<item> Q;
    for (int i = 1; i < m; i++)
        if (dist[i] <= T) {
            if (dist[i] + (st[i + 1] - st[i] - 1) * A <= T) {
                ans += st[i + 1] - st[i];
                continue;
            }
            long add = (T - dist[i]) / A + 1;
            ans += add;
            Q.emplace(get_cnt(i, st[i] + add, st[i + 1] - 1), st[i] + add, i);
        }
    k -= m;
    for (int i = 1; i <= k; i++)
        if (!Q.empty()) {
            item now = Q.top();
            Q.pop();
            ans += now.cnt;
            long pos = now.idx + now.cnt;
            if (pos >= st[now.pos + 1])
                continue;
            Q.emplace(get_cnt(now.pos, pos, st[now.pos + 1] - 1), pos, now.pos);
        }
    printf("%lld\n", ans - 1);

    return 0;
}