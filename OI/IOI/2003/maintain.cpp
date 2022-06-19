#include <bits/stdc++.h>

#define iii tuple<int, int, int>

using namespace std;

const int N = 205;

int n, w, par[N];
set<iii> S;

int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

int main() {
    scanf("%d %d", &n, &w);
    for (int i = 1, a, b, c; i <= w; i++) {
        scanf("%d %d %d", &a, &b, &c);
        iota(par, par + N, 0);
        set<iii> S2;
        S.emplace(c, a, b);
        for (iii e : S) {
            tie(c, a, b) = e;
            if (find(a) != find(b)) {
                par[find(a)] = find(b);
                S2.emplace(c, a, b);
            }
        }
        swap(S, S2);
        int sum = 0;
        for (iii e : S)
            sum += get<0>(e);
        if ((int)S.size() == n - 1)
            printf("%d\n", sum);
        else
            printf("-1\n");
    }

    return 0;
}