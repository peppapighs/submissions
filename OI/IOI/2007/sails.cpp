#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n;
vector<pii> vec;
long t[N];

void update(int x, long k) {
    for (int i = x; i < N; i += i & -i)
        t[i] += k;
}

long query(int x, long ret = 0) {
    for (int i = x; i; i -= i & -i)
        ret += t[i];
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 1, a, b; i <= n; i++)
        scanf("%d %d", &a, &b), vec.emplace_back(a, b);
    sort(vec.begin(), vec.end());
    for (int i = 0, h, k; i < n; i++) {
        auto idx = [&](int x) {
            int l = 0, r = h;
            while (l < r) {
                int m = (l + r + 1) >> 1;
                if (query(m) >= x)
                    l = m;
                else
                    r = m - 1;
            }
            return l;
        };
        tie(h, k) = vec[i];
        int up = idx(query(h - k + 1)), dw = idx(query(h - k + 1) + 1);
        update(up + 1, 1), update(h + 1, -1);
        update(dw + 1, 1), update(dw + 1 + (k - h + up), -1);
    }
    long ans = 0;
    for (int i = 1; i < N; i++) {
        long now = query(i);
        ans += now * (now - 1) / 2;
    }
    printf("%lld\n", ans);

    return 0;
}