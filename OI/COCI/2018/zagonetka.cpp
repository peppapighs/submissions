#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 105;

int n;
int p[N], pos[N], tmp[N];
vector<int> con[N], g[N];
vector<pii> E;

vector<int> toposort(int l, int r) {
    queue<int> Q;
    vector<int> deg(n + 1), ret;
    for (int i = l; i <= r; i++)
        for (int x : g[pos[i]])
            ++deg[x];
    for (int i = l; i <= r; i++)
        if (!deg[pos[i]])
            Q.emplace(pos[i]);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        ret.emplace_back(u);
        for (int v : g[u])
            if (!--deg[v])
                Q.emplace(v);
    }
    return ret;
}

bool ask() {
    vector<int> vec(n + 1);
    for (int i = 1; i <= n; i++)
        vec[tmp[i]] = i;
    printf("query ");
    for (int i = 1; i <= n; i++)
        printf("%d ", vec[i]);
    printf("\n"), fflush(stdout);
    int ret;
    scanf("%d", &ret);
    return !ret;
}

int chk[N];
set<int> cand[N];

void get_cand(int u) {
    chk[u] = true;
    cand[u].emplace(u);
    for (int v : g[u]) {
        if (!chk[v])
            get_cand(v);
        for (int x : cand[v])
            cand[u].emplace(x);
    }
}

void get_answer(int u, vector<int> &ans) {
    chk[u] = true;
    for (int x : cand[u]) {
        if (!chk[x])
            get_answer(x, ans);
    }
    ans.emplace_back(u);
}

vector<int> solve() {
    vector<int> ans;
    for (int i = 1; i <= n; i++)
        if (!chk[i])
            get_cand(i);
    memset(chk, 0, sizeof chk);
    for (int i = 1; i <= n; i++)
        if (!chk[i])
            get_answer(i, ans);
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", p + i);
        pos[p[i]] = i;
    }
    for (int i = n - 1; i; i--)
        for (int j = i + 1; j <= n; j++) {
            for (int k = i; k <= j; k++) {
                g[pos[k]].clear();
                for (int x : con[pos[k]])
                    if (i <= p[x] && p[x] <= j)
                        g[pos[k]].emplace_back(x);
            }
            g[pos[j]].emplace_back(pos[i]);

            vector<int> order = toposort(i, j);
            if ((int)order.size() != j - i + 1)
                continue;
            for (int k = 1; k <= n; k++) {
                if (i <= k && k <= j)
                    tmp[k] = order[k - i];
                else
                    tmp[k] = pos[k];
            }
            if (ask())
                con[pos[i]].emplace_back(pos[j]);
        }
    printf("end\n"), fflush(stdout);

    vector<int> ans;
    for (int i = 1; i <= n; i++)
        g[i].clear(), cand[i].clear();
    for (int i = 1; i <= n; i++)
        for (int x : con[i])
            g[x].emplace_back(i);
    ans = solve();
    for (int i = 1; i <= n; i++)
        tmp[ans[i - 1]] = i;
    for (int i = 1; i <= n; i++)
        printf("%d ", tmp[i]);
    printf("\n"), fflush(stdout);

    memset(chk, 0, sizeof chk);
    for (int i = 1; i <= n; i++)
        g[i].clear(), cand[i].clear();
    for (int i = 1; i <= n; i++)
        for (int x : con[i])
            g[i].emplace_back(x);
    ans = solve();
    for (int i = 1; i <= n; i++)
        tmp[ans[i - 1]] = n - i + 1;
    for (int i = 1; i <= n; i++)
        printf("%d ", tmp[i]);
    printf("\n"), fflush(stdout);

    return 0;
}