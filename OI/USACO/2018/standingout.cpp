#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e5 + 5;

int n;
long ans[N];
string S;
int sz[N], id[N], suf[N], pos[N], lcp[N << 1];
int L[N], R[N];

int get_lcp(int l, int r) {
    if (l > r)
        swap(l, r);
    int ret = 1e9;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            ret = min(ret, lcp[l++]);
        if (r & 1)
            ret = min(ret, lcp[--r]);
    }
    return ret;
}

int main() {
    freopen("standingout.in", "r", stdin);
    freopen("standingout.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < str.size(); j++) {
            id[S.size()] = i;
            sz[S.size()] = str.size() - j;
            S += str[j];
        }
        id[S.size()] = -1;
        S += '#';
    }

    for (int i = 0; i < S.size(); i++)
        suf[i] = i, pos[i] = S[i];
    for (int k = 1; k <= S.size(); k <<= 1) {
        auto chk = [&](int a, int b) {
            if (pos[a] != pos[b])
                return pos[a] < pos[b];
            if (a + k < S.size() && b + k < S.size())
                return pos[a + k] < pos[b + k];
            return a > b;
        };
        sort(suf, suf + S.size(), chk);
        int tmp[N];
        tmp[0] = 0;
        for (int i = 1; i < S.size(); i++)
            tmp[i] = tmp[i - 1] + chk(suf[i - 1], suf[i]);
        for (int i = 0; i < S.size(); i++)
            pos[suf[i]] = tmp[i];
    }
    for (int i = 0, k = 0; i < S.size(); i++)
        if (pos[i] != S.size() - 1) {
            for (int j = suf[pos[i] + 1];
                 S[i + k] == S[j + k] && S[i + k] != '#'; k++)
                ;
            lcp[N + pos[i]] = k;
            if (k)
                --k;
        }
    for (int i = N - 1; i; i--)
        lcp[i] = min(lcp[i << 1], lcp[i << 1 | 1]);

    L[0] = -1;
    for (int i = 1, j = 0; i < S.size(); i++) {
        if (S[suf[i]] == '#') {
            L[i] = -1;
            continue;
        }
        while (j + 1 < i && id[suf[j + 1]] != id[suf[i]])
            ++j;
        if (id[suf[j]] != -1 && id[suf[j]] != id[suf[i]])
            L[i] = j;
        else
            L[i] = -1;
    }
    R[S.size() - 1] = -1;
    for (int i = S.size() - 2, j = S.size() - 1; i >= 0; i--) {
        if (S[suf[i]] == '#') {
            R[i] = -1;
            continue;
        }
        while (j - 1 > i && id[suf[j - 1]] != id[suf[i]])
            --j;
        if (id[suf[j]] != -1 && id[suf[j]] != id[suf[i]])
            R[i] = j;
        else
            R[i] = -1;
    }

    for (int i = 0; i < S.size(); i++) {
        if (id[suf[i]] == -1)
            continue;
        int mx = 0;
        if (L[i] != -1)
            mx = max(mx, get_lcp(L[i], i));
        if (R[i] != -1)
            mx = max(mx, get_lcp(R[i], i));
        if (i != S.size() - 1 && id[suf[i]] == id[suf[i + 1]])
            mx = max(mx, get_lcp(i, i + 1));
        ans[id[suf[i]]] += sz[suf[i]] - mx;
    }
    for (int i = 0; i < n; i++)
        printf("%lld\n", ans[i]);

    return 0;
}