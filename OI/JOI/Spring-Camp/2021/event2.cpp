#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

int n, k;
int L[N], R[N], par[N][19];
vector<int> coord, Q[N];

int solve(int l, int r) {
    int ret = 0;
    for(int i = 18; ~i; i--) if(par[l][i] <= r) {
        ret += (1 << i);
        l = par[l][i];
    }
    return ret;
}

int main() {
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++) {
        scanf("%d %d", L + i, R + i);
        coord.emplace_back(L[i]);
        coord.emplace_back(R[i]);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    for(int i = 1; i <= n; i++) {
        L[i] = lower_bound(coord.begin(), coord.end(), L[i]) - coord.begin();
        R[i] = lower_bound(coord.begin(), coord.end(), R[i]) - coord.begin();
        Q[L[i]].emplace_back(i);
    }

    par[coord.size()][0] = coord.size();
    for(int i = coord.size() - 1; ~i; i--) {
        par[i][0] = par[i + 1][0];
        for(int idx : Q[i])
            par[i][0] = min(par[i][0], R[idx]);
    }

    for(int j = 1; j <= 18; j++)
        for(int i = 0; i <= coord.size(); i++)
            par[i][j] = par[par[i][j - 1]][j - 1];

    int mx_ans = solve(0, coord.size() - 1);

    if(mx_ans < k)
        return !printf("-1\n");

    vector<int> ans;
    set<pii> S = { pii(0, 0), pii(coord.size() - 1, coord.size() - 1) };
    for(int i = 1; i <= n && ans.size() < k; i++) {
        int l = prev(S.lower_bound(pii(R[i], -1e9)))->y;
        int r = S.lower_bound(pii(R[i], -1e9))->x;

        if(L[i] < l || r < R[i])
            continue;

        int now = mx_ans - solve(l, r) + solve(l, L[i]) + 1 + solve(R[i], r);
        if(now >= k) {
            S.emplace(L[i], R[i]);
            ans.emplace_back(i);
            mx_ans = now;
        }
    }

    for(int x : ans) printf("%d\n", x);

    return 0;
}