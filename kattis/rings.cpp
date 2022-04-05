#include <bits/stdc++.h>

using namespace std;
using iii = tuple<double, double, double>;

const int N = 105;

int n;
int par[N], sz[N];

int find(int x) {
    return par[x] = x == par[x] ? x : find(par[x]);
}

void unite(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) return;
    sz[b] += sz[a], par[a] = b;
}


int main() {
    while(scanf("%d", &n), n != -1) {
        iota(par, par + n, 0), fill(sz, sz + n, 1);
        vector<iii> ring;
        for(int i = 0; i < n; i++) {
            double a, b, c;
            scanf("%lf %lf %lf", &a, &b, &c);
            ring.emplace_back(a, b, c);
        }
        for(int i = 0; i < n; i++) {
            auto &[x1, y1, r1] = ring[i];
            for(int j = i + 1; j < n; j++) {
                auto &[x2, y2, r2] = ring[j];
                double d = hypot(x2 - x1, y2 - y1);
                if(fabs(r1 - r2) <= d && d <= r1 + r2)
                    unite(i, j);
            }
        }
        int ans = 1;
        for(int i = 0; i < n; i++) if(find(i) == i)
            ans = max(ans, sz[i]);
        printf("The largest component contains %d ring", ans);
        if(ans > 1) printf("s.\n");
        else printf(".\n");
    }

    return 0;
}