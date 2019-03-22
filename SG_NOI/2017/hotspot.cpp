#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second
#define long long long

using namespace std;

const int N = 5e3+5;

int n, m, k;
vector<int> g[N];
double sum[N];

vector<int> sssp(int src) {
    priority_queue<pii, vector<pii>, greater<pii> > Q;
    vector<int> d(n);
    fill(d.begin(), d.end(), 1e9);
    Q.emplace(d[src] = 0, src);
    while(!Q.empty()) {
        pii now = Q.top(); Q.pop();
        if(d[now.y] != now.x) continue;
        for(int v : g[now.y]) if(d[v] > d[now.y] + 1)
            Q.emplace(d[v] = d[now.y] + 1, v);
    }
    return d;
}

vector<long> cnt(vector<bool> &pth, vector<int> &d, int src) {
    queue<pii> Q;
    vector<long> ret(n);
    Q.emplace(ret[src] = 1, src);
    while(!Q.empty()) {
        pii now = Q.front(); Q.pop();
        if(ret[now.y] != now.x) continue;
        for(int v : g[now.y]) if(pth[now.y] && d[now.y] + 1 == d[v])
            Q.emplace(ret[v] += ret[now.y], v);
    }
    return ret;
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    scanf("%d", &k);
    for(int i = 1, a, b; i <= k; i++) {
        scanf("%d %d", &a, &b);
        priority_queue<pii, vector<pii>, greater<pii> > Q;
        vector<int> dA = sssp(a), dB = sssp(b);
        vector<bool> pth(n);
        for(int j = 0; j < n; j++) if(dA[j] + dB[j] == dA[b]) pth[j] = true;
        vector<long> cA = cnt(pth, dA, a), cB = cnt(pth, dB, b);
        for(int j = 0; j < n; j++) if(pth[j]) sum[j] += (1.0*cA[j]*cB[j]/cA[b]);
    } 
    pair<double, int> ans(0, -1);
    for(int i = 0; i < n; i++) ans = max(ans, make_pair(sum[i], i));
    printf("%d\n", ans.y);

    return 0;
}