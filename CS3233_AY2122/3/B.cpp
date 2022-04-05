#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e3 + 5;

int n;
pii A[N];
unordered_set<long> cnt;

long f(pii p) {
    return p.x * 98765431 + p.y;
}

void solve() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d %d", &A[i].x, &A[i].y);
        cnt.insert(f(A[i]));
    }
    sort(A + 1, A + n + 1);

    long ans = 0;
    for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) {
        pii &p = A[i], &q = A[j];

        int dx = q.x - p.x, dy = q.y - p.y;

        if(dx == 0 && dy == 0) continue;

        pii r(q.x + dy, q.y - dx);
        pii s(r.x - dx, r.y - dy);
        ans += 1ll * cnt.count(f(r)) * cnt.count(f(s));
    }

    printf("%lld\n", ans >> 1);

    cnt.clear();
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}
