#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n;
vector<int> g[N];

bool chk(vector<int> &vec, int k, int pv) {
    int l = 0, r = vec.size() - 1;
    for(int i = 0; i < vec.size() / 2; i++, l++, r--) {
        if(l == pv) ++l;
        if(r == pv) --r;
        if(vec[l] + vec[r] < k) return false;
    }
    return true;
}

int dfs(int u, int p, int k) {
    vector<int> child; 
    for(int v : g[u]) if(v != p) {
        int x = dfs(v, u, k);
        if(x == -1) return -1;
        child.emplace_back(min(k, x + 1));
    }
    sort(child.begin(), child.end());
    vector<int> chk1 = child, chk2 = child;

    if(chk1.size() & 1) chk1.insert(chk1.begin(), 0);
    bool all = chk(chk1, k, -1);

    if(chk2.size() % 2 == 0) chk2.insert(chk2.begin(), 0);
    int l = 0, r = chk2.size() - 1, ret = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(chk(chk2, k, mid)) ret = mid, l = mid + 1;
        else r = mid - 1;
    }

    if(u == 1) return !all;
    if(ret != -1) return chk2[ret];
    if(all) return 0;
    return -1;
}

int main() {
    freopen("deleg.in", "r", stdin);
    freopen("deleg.out", "w", stdout);

    scanf("%d", &n);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    int l = 1, r = n - 1;
    while(l < r) {
        int mid = (l + r + 1) >> 1;
        if(dfs(1, 0, mid) == 0) l = mid;
        else r = mid - 1;
    }
    printf("%d\n", l);

    return 0;
}