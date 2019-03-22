#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, q, suf[N], pos[N];
int lcp[N << 1];
char S[N];

int query(int l, int r) {
    if(l == r) return n - suf[l] + 1;
    if(l > r) swap(l, r);
    int ret = 1e9;
    for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if(l & 1) ret = min(ret, lcp[l++]);
        if(r & 1) ret = min(ret, lcp[--r]);
    }
    return ret;
}

int main() {
    scanf("%d %d", &n, &q);
    scanf(" %s", S+1);
    for(int i = 1; i <= n; i++) suf[i] = i, pos[i] = S[i];
    for(int k = 1; k <= n; k <<= 1) {
        auto chk = [&](int a, int b) {
            if(pos[a] != pos[b]) return pos[a] < pos[b];
            if(a + k <= n && b + k <= n) return pos[a + k] < pos[b + k];
            else return a > b;
        };
        sort(suf + 1, suf + n + 1, chk);
        int tmp[N]; tmp[1] = 1;
        for(int i = 1; i < n; i++) tmp[i + 1] = tmp[i] + chk(suf[i], suf[i + 1]);
        for(int i = 1; i <= n; i++) pos[suf[i]] = tmp[i];
    }
    for(int i = 1, k = 0; i <= n; i++) if(pos[i] != n) {
        for(int j = suf[pos[i] + 1]; S[i + k] == S[j + k]; k++);
        lcp[pos[i] + N] = k;
        if(k) --k;
    }
    for(int i = N-1; i; i--) lcp[i] = min(lcp[i<<1], lcp[i<<1|1]);
    set<int> S;
    S.emplace(pos[1]);
    for(int i = 1, T, a; i <= q; i++) {
        scanf("%d %d", &T, &a);
        if(T == 1) S.emplace(pos[a]);
        else {
            int mx = 0;
            auto it = S.lower_bound(pos[a]);
            if(it != S.end()) mx = max(mx, query(pos[a], *it));
            if(it != S.begin()) --it, mx = max(mx, query(pos[a], *it));
            printf("%d\n", mx);
        }
    } 

    return 0;
}