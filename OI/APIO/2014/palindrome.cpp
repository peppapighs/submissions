#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 3e5 + 5;

int n;
int t[N][26], len[N], link[N], occ[N], idx, suff;
char S[N];

void add(int pos) {
    int cur = suff, x = S[pos] - 'a';
    while (pos - 1 - len[cur] < 0 || S[pos - 1 - len[cur]] != S[pos])
        cur = link[cur];
    if (t[cur][x]) {
        suff = t[cur][x];
        ++occ[t[cur][x]];
        return;
    }
    suff = ++idx;
    len[idx] = len[cur] + 2, t[cur][x] = idx, occ[idx] = 1;
    if (len[idx] == 1) {
        link[idx] = 2;
        return;
    }
    cur = link[cur];
    while (pos - 1 - len[cur] < 0 || S[pos - 1 - len[cur]] != S[pos])
        cur = link[cur];
    link[idx] = t[cur][x];
}

void init_tree() {
    idx = suff = 2;
    len[1] = -1, len[2] = 0;
    link[1] = 1, link[2] = 1;
}

int main() {
    scanf("%s", S + 1);
    n = strlen(S + 1);
    init_tree();
    for (int i = 1; i <= n; i++)
        add(i);
    long ans = 0;
    for (int i = idx; i > 2; i--) {
        occ[link[i]] += occ[i];
        ans = max(ans, 1ll * len[i] * occ[i]);
    }
    printf("%lld\n", ans);

    return 0;
}