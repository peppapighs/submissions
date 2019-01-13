#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int n, a, b;
int A[N], dp[N<<1];

void update(int x) { for(dp[x += N] = true; x != 1; x >>= 1) dp[x>>1] = dp[x] | dp[x^1]; }

bool query(int l, int r) {
    bool ret = false;
    for(l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
        if(l & 1) ret |= dp[l++];
        if(r & 1) ret |= dp[--r];
    }
    return ret;
}

bool f(int m) {
    memset(dp, 0, sizeof dp);
    set<int, greater<int> > S;
    update(0);
    for(int i = 1; i < a; i++) if(A[i] >= m) S.emplace(i);
    for(int i = a; i <= n; i++) {
        if(A[i] >= m) S.emplace(i);
        if(i - b > 0) S.erase(i - b);
        if(S.empty()) continue;
        int Q = *S.begin();
        if(query(max(0, i-b), min(i-a, Q-1))) update(i);
    }
    return query(n, n);
}

int main() {
    scanf("%d %d %d", &n, &a, &b);
    for(int i = 1; i <= n; i++) scanf("%d", A+i);
    int l = 0, r = 1e9;
    bool valid = false;
    while(l < r) {
        int m = (l + r + 1) >> 1;
        if(f(m)) l = m, valid = true;
        else r = m-1;
    }
    if(valid) printf("%d\n", l);
    else printf("-1\n");

    return 0;
}