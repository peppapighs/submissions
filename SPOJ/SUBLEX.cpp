#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;

int n, q;
int pos[N], sa[N], tmp[N], lcp[N];
char S[N];

void build_sa() {
    tmp[1] = 1;
    for (int i = 1; i <= n; i++)
        sa[i] = i, pos[i] = S[i];
    for (int gap = 1; gap <= n; gap <<= 1) {
        auto cmp = [&](int a, int b) {
            if (pos[a] != pos[b])
                return pos[a] < pos[b];
            a += gap, b += gap;
            return (a <= n && b <= n) ? pos[a] < pos[b] : a > b;
        };
        sort(sa + 1, sa + 1 + n, cmp);
        for (int i = 2; i <= n; i++)
            tmp[i] = tmp[i - 1] + cmp(sa[i - 1], sa[i]);
        for (int i = 1; i <= n; i++)
            pos[sa[i]] = tmp[i];
    }

    for (int i = 1, k = 0; i <= n; i++)
        if (pos[i] != n) {
            for (int j = sa[pos[i] + 1]; S[i + k] == S[j + k]; k++)
                ;
            lcp[pos[i]] = k;
            if (k)
                --k;
        }
}

long cnt[N];

int main() {
    scanf(" %s", S + 1);
    n = strlen(S + 1);
    build_sa();

    for (int i = 1; i <= n; i++) {
        cnt[i] = n - sa[i] - lcp[i - 1] + 1;
        cnt[i] += cnt[i - 1];
    }

    scanf("%d", &q);
    for (int t = 1, k; t <= q; t++) {
        scanf("%d", &k);
        int idx = lower_bound(cnt + 1, cnt + 1 + n, k) - cnt;
        char c = '\0';
        swap(c, S[sa[idx] + lcp[idx - 1] + k - cnt[idx - 1]]);
        printf("%s\n", S + sa[idx]);
        swap(c, S[sa[idx] + lcp[idx - 1] + k - cnt[idx - 1]]);
    }

    return 0;
}