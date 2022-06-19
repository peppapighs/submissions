#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, col[N];
char S[N], ans[N];
stack<int> st;
vector<int> v[N];

void solve(int l, int r) {
    if (l > r)
        return;
    vector<int> &now = v[col[l]];
    auto it = --upper_bound(now.begin(), now.end(), r);
    ans[l] = '(', ans[*it] = ')';
    solve(l + 1, *it - 1), solve(*it + 1, r);
}

int t[N][26], par[N];

int main() {
    scanf("%s", S + 1);
    n = strlen(S + 1);
    int ptr = 0, u = 0;
    for (int i = 1; i <= n; i++) {
        int c = S[i] - 'a', id;
        if (st.empty() || st.top() != c) {
            st.emplace(c);
            if (!t[u][c])
                t[u][c] = ++ptr, par[ptr] = u;
            id = t[u][c], u = t[u][c];
        } else {
            id = u, u = par[u];
            st.pop();
        }
        col[i] = id;
        v[id].emplace_back(i);
    }
    if (st.size())
        return !printf("-1\n");
    solve(1, n);
    printf("%s\n", ans + 1);

    return 0;
}