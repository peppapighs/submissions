#include <bits/stdc++.h>

#define long long long
#define x first
#define y second

using namespace std;
using pii = pair<long, long>;

long cross(pii a, pii b) {
    return a.x * b.y - a.y * b.x;
}

pii vec(pii a, pii b) {
    return pii(b.x - a.x, b.y - a.y);
}

const int N = 55;

int n;
pii A[N];
long cnt[N][N], same[N][N];

int main() {
    while(scanf("%d", &n), n != 0) {
        memset(cnt, 0, sizeof cnt);
        memset(same, 0, sizeof cnt);

        for(int i = 0; i < n; i++) scanf("%lld %lld", &A[i].x, &A[i].y);
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
            if(i == j) continue;
            pii l1 = vec(A[i], A[j]);
            for(int k = 0; k < n; k++) {
                pii l2 = vec(A[i], A[k]);
                if(cross(l1, l2) > 0)
                    cnt[i][j] |= (1ll << k);
                if(cross(l1, l2) == 0)
                    same[i][j] |= (1ll << k);
            }
        }

        long ans = 0, all = (1ll << n) - 1;
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) for(int k = 0; k < n; k++) {
            if(i == j || j == k || i == k) continue;
            if(cross(vec(A[i], A[j]), vec(A[j], A[k])) <= 0)
                continue;
            long now = cnt[i][j] & cnt[j][k];
            now &= all - (now & cnt[k][i]);
            now &= all - (same[i][j] | same[j][k] | same[k][i]);

            ans += __builtin_popcountll(now);
        }

        printf("%lld\n", ans >> 2);
    }

    return 0;
}