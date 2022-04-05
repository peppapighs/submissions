#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int T;

int n, m;
vector<int> g[N];

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d", &n, &m);
        for(int i = 0, a, b; i < m; i++) {
            scanf("%d %d", &a, &b);
            g[a].emplace_back(b);
            g[b].emplace_back(a);
        }

        vector<int> ans = {0};
        set<int> cand(g[0].begin(), g[0].end());

        while(!cand.empty()) {
            int u = *cand.begin();
            ans.emplace_back(u);

            set<int> nex;
            cand.erase(cand.begin());

            for(int v : g[u]) if(cand.find(v) != cand.end()) {
                nex.emplace(v);
            }

            cand = nex;
        }

        sort(ans.begin(), ans.end());
        for(int i = 0; i < ans.size(); i++) {
            printf("%d", ans[i]);
            if(i != ans.size() - 1) printf(" ");
        }
        printf("\n");

        for(int i = 0; i < N; i++) g[i].clear();
    }

    return 0;
}