#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n, k, z1, z2;
int A[N], dp_l[N], dp_r[N], pref[N], mn[N], mx[N];
vector<int> L, R, col[N];

vector<int> solve(vector<int> &vec, int dp[]) {
    fill_n(dp, N, 1e9);

    vector<int> ret(n + 2, 1e9);
    for(int i = (int)vec.size() - 1; ~i; i--) {
        int now = vec[i];
        for(int x : col[now]) {
            if(i == (int)vec.size() - 1) dp[x] = x;
            else {
                vector<int> &nex = col[vec[i + 1]];
                auto it = upper_bound(nex.begin(), nex.end(), x);
                if(it == nex.end()) continue;

                dp[x] = dp[*it];
            }
            if(i == 0) ret[x] = dp[x];
        }
    }
    for(int i = n; i; i--) ret[i] = min(ret[i], ret[i + 1]);
    return ret;
}

int main() {
    fill_n(mn, N, 1e9);

    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        col[A[i]].emplace_back(i);
        mn[A[i]] = min(mn[A[i]], i);
        mx[A[i]] = max(mx[A[i]], i);
    }

    scanf("%d %d", &z1, &z2);
    for(int i = 1, a; i <= z1; i++) {
        scanf("%d", &a);
        L.emplace_back(a);
    }
    for(int i = 1, a; i <= z2; i++) {
        scanf("%d", &a);
        R.emplace_back(a);
    }

    vector<int> ans_l = solve(L, dp_l);

    reverse(A + 1, A + n + 1);
    for(int i = 1; i <= k; i++) {
        for(int &x : col[i])
            x = n - x + 1;
        reverse(col[i].begin(), col[i].end());
    }
    vector<int> ans_r = solve(R, dp_r);

    reverse(A + 1, A + n + 1);
    reverse(ans_r.begin(), ans_r.end());
    for(int &x : ans_r) if(x != 1e9) x = n - x + 1;

    for(int i = 1; i <= k; i++) if(mn[i] <= n && 1 <= mx[i]) {
        int l = ans_l[mn[i] + 1], r = ans_r[mx[i] - 1];
        if(l > r || l == 1e9 || r == 1e9) continue;
        ++pref[l], --pref[r + 1];
    }

    vector<int> ret;
    for(int i = 1; i <= n; i++) {
        pref[i] += pref[i - 1];
        if(A[i] == L.back() && pref[i] > 0)
            ret.emplace_back(i);
    }

    printf("%d\n", (int)ret.size());
    for(int x : ret) printf("%d ", x);
    printf("\n");

    return 0;
}