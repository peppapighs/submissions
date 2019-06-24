#include <bits/stdc++.h>

#define long long long
#define iii tuple<int, int, int>

using namespace std;

const int N = 2e5+5;

int par[N];

int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

int n, m, pos[N], chk[N];
int T;
vector<iii> E;

int main() {
    iota(pos, pos+N, 0), iota(par, par+N, 0);
    scanf("%d %d", &n, &m);
    for(int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        E.emplace_back(a, b, c);
    }
    scanf("%d", &T);
    sort(pos+1, pos+m+1, [&](const int &a, const int &b) {
        return get<2>(E[a-1]) > get<2>(E[b-1]);
    });
    int cnt = 0;
    long ans = 0;
    for(int i = 1, a, b, c; i <= m; i++) {
        tie(a, b, c) = E[pos[i]-1];
        if(find(a) != find(b)) {
            ++cnt, chk[pos[i]] = true;
            par[find(a)] = find(b);
            ans += c;
        } 
    }
    for(int i = 1; i <= m; i++) if(!chk[pos[i]])  {
        ans += get<2>(E[pos[i]-1]);
        chk[pos[i]] = true;
        ++cnt;
        break;
    }
    if(cnt != n) printf("-1\n");
    else {
        printf("%lld\n", ans);
        if(T == 2) for(int i = 1; i <= m; i++) if(chk[i]) printf("%d ", i);
        printf("\n");
    }

    return 0;
}