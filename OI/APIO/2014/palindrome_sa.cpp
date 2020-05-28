#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 6e5+5;

int n, sz;
int pos[N], sa[N], tmp[N], lcp[N][20];
char S[N];

void build_sa() {
    tmp[1] = 1;
    for(int i = 1; i <= sz; i++) sa[i] = i, pos[i] = S[i];
    for(int gap = 1; gap <= sz; gap <<= 1) {
        auto cmp = [&](int a, int b) {
            if(pos[a] != pos[b]) return pos[a] < pos[b];
            a += gap, b += gap;
            return (a <= sz && b <= sz) ? pos[a] < pos[b] : a > b;
        };
        sort(sa + 1, sa + 1 + sz, cmp);
        for(int i = 1; i < sz; i++) tmp[i + 1] = tmp[i] + cmp(sa[i], sa[i + 1]);
        for(int i = 1; i <= sz; i++) pos[sa[i]] = tmp[i];
    }

    for(int i = 1, k = 0; i <= sz; i++) if(pos[i] != sz) {
        for(int j = sa[pos[i] + 1]; S[i + k] == S[j + k]; k++);
        lcp[pos[i]][0] = k;
        if(k) --k;
    }
    for(int j = 0; j  < 19; j++) for(int i = 1; i <= sz; i++) {
        if(i + (1 << j) > sz) continue;
        lcp[i][j + 1] = min(lcp[i][j], lcp[i + (1 << j)][j]);
    }
}

int find_lcp(int l, int r) {
    if(l > r) swap(l, r);
    int k = 31 - __builtin_clz(r - l);
    return min(lcp[l][k], lcp[r - (1 << k)][k]);
}

int lp[N], cnt[N >> 1];
long ans;

void solve(int odd) {
    int len = 0;
    long sum; 
    for(int i = 1; i <= sz + 1; i++) {
        sum = 0;
        while(len > lcp[i - 1][0]) {
            sum += cnt[len], cnt[len] = 0;
            ans = max(ans, sum * (2 * len - odd));
            --len;
        }
        if(i == sz + 1) continue;
        cnt[len] += sum;
        len = max(len, lp[i]);
        ++cnt[lp[i]];
    }
}

int main() {
    scanf(" %s", S + 1);
    n = strlen(S + 1), sz = 2 * n + 1;
    S[n + 1] = '#';
    for(int i = 1; i <= n; i++) S[sz - i + 1] = S[i];
    build_sa();

    for(int i = 1; i <= n; i++) lp[pos[i]] = find_lcp(pos[i], pos[sz - i + 1]);
    solve(1);
    lp[pos[1]] = 0;
    for(int i = 2; i <= n; i++) lp[pos[i]] = find_lcp(pos[i], pos[sz - i + 2]);
    solve(0);
    
    printf("%lld\n", ans);

    return 0;
}