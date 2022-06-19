#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n;
int A[N], par[N], l[N], r[N];

int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

int unite(int a, int b) {
    a = find(a), b = find(b);
    par[a] = b;
    l[b] = min(l[b], l[a]);
    r[b] = max(r[b], r[a]);
    return b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i);

    vector<int> candid;
    for (int i = 1; i <= n; i++) {
        candid.emplace_back(i);
        par[i] = i;
        l[i] = i - 1, r[i] = i + 1;
    }
    vector<vector<int>> ans;
    while (!candid.empty()) {
        vector<int> L, R;
        ans.emplace_back(vector<int>());
        for (int x : candid) {
            if (A[x] < A[find(l[x])]) {
                L.emplace_back(x);
                ans.back().emplace_back(A[x]);
            } else if (A[x] < A[find(r[x])]) {
                R.emplace_back(x);
                ans.back().emplace_back(A[x]);
            }
        }
        vector<int> change;
        for (int x : L)
            change.emplace_back(unite(x, l[x]));
        for (int x : R)
            change.emplace_back(unite(x, r[x]));

        set<int> S;
        for (int x : change)
            if (find(x) == x)
                S.emplace(x), S.emplace(find(l[x])), S.emplace(find(r[x]));
        candid = vector<int>(S.begin(), S.end());
        if (ans.back().empty())
            ans.pop_back();
    }
    printf("%d\n", ans.size());
    for (vector<int> &v : ans) {
        for (int x : v)
            printf("%d ", x);
        printf("\n");
    }
    for (int i = 1; i <= n; i++)
        if (find(i) == i)
            printf("%d ", A[i]);
    printf("\n");

    return 0;
}