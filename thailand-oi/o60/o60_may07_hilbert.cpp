#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

pii rot(pii p, int n, int k) {
    int a = p.x, b = p.y;
    int sz = (1 << n) + 1;
    if(k == 1) return { a, b };
    if(k == 2) return { sz - b , a }; 
    if(k == 3) return { sz - a, sz - b };
    if(k == 4) return { b, sz - a };
}

long dist(pii p, int n) {
    int a = p.x, b = p.y;
    if(n == 1) {
        if(a == 1 && b == 1) return 0;
        if(a == 1 && b == 2) return 1;
        if(a == 2 && b == 2) return 2;
        if(a == 2 && b == 1) return 3;
    }
    int ca = (1 << (n-1)) + 1, cb = (1 << (n-1)) + 1;
    long ndist = (1ll << ((n-1ll) << 1ll)) - 1ll;
    if(n & 1) {
        if(a < ca && b < cb) return dist(pii(a, b), n-1); 
        if(a < ca && b >= cb) return ndist + 1 + ndist - dist(rot(pii(a, b - cb + 1), n-1, 4), n-1);
        if(a >= ca && b >= cb) return 2ll*ndist + 2 + ndist - dist(rot(pii(a - ca + 1, b - cb + 1), n-1, 4), n-1);
        if(a >= ca && b < cb) return 3ll*ndist + 3 + dist(rot(pii(a - ca + 1, b), n-1, 3), n-1);
    } else {
        if(a < ca && b < cb) return dist(pii(a, b), n-1);
        if(a >= ca && b < cb) return ndist + 1 + ndist - dist(rot(pii(a - ca + 1, b), n-1, 2), n-1);
        if(a >= ca && b >= cb) return 2ll*ndist + 2 + ndist - dist(rot(pii(a - ca + 1, b - cb + 1), n-1, 2), n-1);
        if(a < ca && b >= cb) return 3ll*ndist + 3 + dist(rot(pii(a, b - cb + 1), n-1, 3), n-1);
    }
}

pii get(long k, int n) {
    if(n == 1) {
        if(k == 0) return { 1, 1 };
        if(k == 1) return { 1, 2 };
        if(k == 2) return { 2, 2 };
        if(k == 3) return { 2, 1 };
    }
    long ndist = (1ll << ((n-1ll) << 1ll)) - 1ll;
    if(n & 1) {
        if(k <= ndist) return get(k, n-1);
        else if(k <= 2ll*ndist + 1) {
            pii ret = rot(get(ndist - k + ndist + 1, n-1), n-1, 2);
            return { ret.x, ret.y + (1<<(n-1)) };
        } else if(k <= 3ll*ndist + 2) {
            pii ret = rot(get(ndist - k + 2*ndist + 2, n-1), n-1, 2);
            return { ret.x + (1<<(n-1)), ret.y + (1<<(n-1)) };
        } else {
            pii ret = rot(get(k - 3*ndist - 3, n-1), n-1, 3);
            return { ret.x+ (1<<(n-1)), ret.y };
        }
    } else {
        if(k <= ndist) return get(k, n-1);
        else if(k <= 2ll*ndist + 1) {
            pii ret = rot(get(ndist - k + ndist + 1, n-1), n-1, 4);
            return { ret.x + (1<<(n-1)), ret.y };
        } else if(k <= 3ll*ndist + 2) {
            pii ret = rot(get(ndist - k + 2*ndist + 2, n-1), n-1, 4);
            return { ret.x + (1<<(n-1)), ret.y + (1<<(n-1)) };
        } else {
            pii ret = rot(get(k - 3*ndist - 3, n-1), n-1, 3);
            return { ret.x, ret.y + (1<<(n-1)) };
        }
    }
}

int q;

int main() {
    scanf("%d", &q);
    while(q--) {
        int T;
        scanf("%d", &T);
        if(T == 1) {
            int a, b, n = 1;
            scanf("%d %d", &a, &b);
            while(max(a, b) > (1<<n)) ++n; 
            printf("%lld\n", dist(pii(a, b), n));
        } else {
            long k, n = 1;
            scanf("%lld", &k);
            while(k > (1ll << (n << 1ll)) - 1ll) ++n;
            pii ans = get(k, n);
            printf("%d %d\n", ans.x, ans.y);
        }
    }

    return 0;
}