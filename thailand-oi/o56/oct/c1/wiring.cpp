#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int T;
int deg[N];
int A[N], B[N];
vector<int> g[N];

int main() {
    scanf("%d", &T);
    while (T--) {
        int n;
        memset(deg, 0, sizeof deg);
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", A + i), g[i].clear();
        for (int i = 1; i <= n; i++)
            scanf("%d", B + i);
        for (int i = 1; i <= n; i++)
            if (A[i] && B[i] && A[i] != B[i]) {
                g[A[i]].emplace_back(B[i]);
                ++deg[B[i]];
            }
        queue<int> Q;
        for (int i = 1; i <= n; i++)
            if (!deg[A[i]])
                Q.emplace(A[i]);
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (int v : g[u])
                if (!--deg[v])
                    Q.emplace(v);
        }
        bool valid = true;
        for (int i = 1; i <= n; i++)
            if (deg[A[i]])
                valid = false;
        if (valid)
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}
