#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define x first
#define y second

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

//-----------------------------------------------------------

const int N = 2e6 + 5;

struct tupe {
    int a, b, x;
    tupe(int a, int b, int x) : a(a), b(b), x(x) {}
};

int n, ans;
int mx1, mx2, e, v;
bool chk[N], vis[N];
vector<pii> g[N];
vector<int> cmp;
vector<tupe> E;

int get(int k) { return lower_bound(cmp.begin(), cmp.end(), k) - cmp.begin(); }

void dfs(int u) {
    v++;
    int t = cmp[u];
    if (t > mx1)
        swap(t, mx1);
    if (t > mx2)
        swap(t, mx2);
    vis[u] = true;
    for (pii v : g[u]) {
        if (!chk[v.y])
            e++, chk[v.y] = true;
        if (!vis[v.x])
            dfs(v.x);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        E.emplace_back(a, b, i);
        cmp.emplace_back(a);
        cmp.emplace_back(b);
    }
    sort(cmp.begin(), cmp.end());
    cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());
    for (tupe t : E) {
        int a = get(t.a), b = get(t.b);
        g[a].emplace_back(b, t.x);
        g[b].emplace_back(a, t.x);
    }
    for (int i = 0; i < cmp.size(); i++)
        if (!vis[i]) {
            mx1 = -1, mx2 = -1;
            v = 0, e = 0;
            dfs(i);
            if (e == v - 1)
                ans = max(ans, mx2);
            else if (e == v)
                ans = max(ans, mx1);
            else
                return !printf("-1\n");
        }
    printf("%d\n", ans);

    return 0;
}