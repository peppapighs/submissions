#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

int n, m, ans;
int dsu[N];
vector<iii> E;

int find(int x) { return dsu[x] = x == dsu[x] ? x : find(dsu[x]); }

int main() {
    iota(dsu, dsu + N, 0);
    scanf("%d %d", &n, &m);
    for (int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        E.emplace_back(c, a, b);
    }
    sort(E.begin(), E.end());
    for (int i = 0, j; i < m;) {
        int cnt = 0, mrg = 0;
        for (j = i; j < m && get<0>(E[i]) == get<0>(E[j]); j++) {
            int a, b, c;
            tie(c, a, b) = E[j];
            int pa = find(a), pb = find(b);
            if (pa != pb)
                ++cnt;
        }
        for (; i < j; i++) {
            int a, b, c;
            tie(c, a, b) = E[i];
            int pa = find(a), pb = find(b);
            if (pa != pb) {
                ++mrg;
                dsu[pa] = pb;
            }
        }
        ans += cnt - mrg;
    }
    printf("%d\n", ans);

    return 0;
}