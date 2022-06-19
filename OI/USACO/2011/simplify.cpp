#include <bits/stdc++.h>

#define long long long
#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 4e4 + 5;
const int MOD = 1e9 + 7;

int n, m, par[N];
long ans = 1, sum;
vector<iii> E;

int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

int main() {
    iota(par, par + N, 0);
    scanf("%d %d", &n, &m);
    for (int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        E.emplace_back(c, a, b);
    }
    sort(E.begin(), E.end());
    for (int i = 0, j; i < m;) {
        int sz = 0, cnt = 0;
        set<pii> S;
        for (j = i; j < m && get<0>(E[j]) == get<0>(E[i]); j++) {
            int a, b, c;
            tie(c, a, b) = E[j];
            int pa = find(a), pb = find(b);
            if (pa > pb)
                swap(pa, pb);
            if (pa != pb) {
                S.emplace(pa, pb);
                ++sz;
            }
        }
        for (; i < j; i++) {
            int a, b, c;
            tie(c, a, b) = E[i];
            if (find(a) != find(b)) {
                par[find(a)] = find(b);
                sum += c, ++cnt;
            }
        }
        if (sz == 2 && cnt == 1)
            ans = (ans * 2) % MOD;
        if (sz == 3) {
            if (cnt == 1 && S.size() == 1)
                ans = (ans * 3) % MOD;
            if (cnt == 2 && S.size() == 3)
                ans = (ans * 3) % MOD;
            if (cnt == 2 && S.size() == 2)
                ans = (ans * 2) % MOD;
        }
    }
    printf("%lld %lld\n", sum, ans);

    return 0;
}