#include <bits/stdc++.h>

#define long long long
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

int n;
int A[N], H[N], C[N], indeg[N];
map<int, long> f[N];

int main() {
    scanf("%d", &n);

    vector<int> coord;
    for(int i = 1; i <= n; i++) {
        scanf("%d %d %d", A + i, H + i, C + i);
        coord.emplace_back(H[i]);
        ++indeg[A[i]];
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    for(int i = 1; i <= n; i++)
        H[i] = lower_bound(coord.begin(), coord.end(), H[i]) - coord.begin();

    vector<int> chk(n + 1);
    queue<int> Q;
    for(int i = 1; i <= n; i++) if(!indeg[i])
        Q.emplace(i), chk[i] = 1;

    while(!Q.empty()) {
        int u = Q.front(); Q.pop();

        f[u][H[u] + 1] += C[u];

        long sum = 0;
        bool valid = false;
        while(f[u].begin()->x != H[u] + 1) {
            auto it = prev(f[u].find(H[u] + 1));
            auto p = *it;

            f[u].erase(it);
            sum += p.y;

            if(C[u] < sum) {
                f[u][p.x] += sum - C[u];
                f[u][0] += C[u];
                valid = true;
                break;
            }
        }

        if(!valid)
            f[u][0] += sum;

        if(f[A[u]].size() < f[u].size())
            swap(f[A[u]], f[u]);
        for(auto p : f[u])
            f[A[u]][p.x] += p.y;
        f[u].clear();

        if(!--indeg[A[u]])
            Q.emplace(A[u]), chk[A[u]] = 1;
    }

    long ans = 0;
    for(int i = 1; i <= n; i++) if(!chk[i]) {
        vector<int> cyc = {i};
        while(A[cyc.back()] != i)
            cyc.emplace_back(A[cyc.back()]);
        
        long sum_cost = 0;
        map<int, long> f_cyc, sub;
        for(int u : cyc) {
            chk[u] = 1;
            sum_cost += C[u];
            sub[H[u]] += C[u];

            if(f_cyc.size() < f[u].size())
                swap(f_cyc, f[u]);
            for(auto p : f[u])
                f_cyc[p.x] += p.y;
        }

        for(auto p : sub) if(!f_cyc.count(p.x))
            f_cyc[p.x] = 0;

        long pref = 0, ret = 1e18;
        for(auto p : f_cyc) {
            pref += f_cyc[p.x];
            f_cyc[p.x] = pref;
        }

        for(auto p : f_cyc)
            ret = min(ret, sum_cost - sub[p.x] + f_cyc[p.x]);

        ans += ret;
    }

    printf("%lld\n", ans);

    return 0;
}