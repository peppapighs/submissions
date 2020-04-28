#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 3e5+5;

int n, m, l, q;
bitset<N> block, chk1, chk2;
vector<pii> g[N], h[N];

void update(int u, int left) {
    queue<pii> Q;
    chk1[u] = 1, Q.emplace(u, left); 
    while(!Q.empty()) {
        pii now = Q.front(); Q.pop();
        if(now.y == 0) continue;
        for(pii v : g[now.x]) if(!block[v.y] && !chk1[v.x]) {
            chk1[v.x] = 1;
            Q.emplace(v.x, now.y - 1);
        }
    } 
}

bool solve(int u, int left) {
    queue<pii> Q;
    chk2[u] = 1, Q.emplace(u, left); 
    while(!Q.empty()) {
        pii now = Q.front(); Q.pop();
        if(chk1[now.x]) return true;
        if(now.y == 0) continue;
        for(pii v : h[now.x]) if(!block[v.y] && !chk2[v.x]) {
            chk2[v.x] = 1;
            Q.emplace(v.x, now.y - 1);
        }
    }
    return false;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &l, &q);
    for(int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b, i);
        h[b].emplace_back(a, i);
    }
    int ptr = m;
    for(int i = 1, T, a, b; i <= q; i++) {
        scanf("%d %d", &T, &a);
        if(T == 2) block[a] = 1;
        else {
            scanf("%d", &b);
            if(T == 1) {
                update(a, (l + 1) / 2);
                printf("%d\n", solve(b, l / 2));
                chk1.reset(), chk2.reset();
            } else {
                g[a].emplace_back(b, ++ptr);
                h[b].emplace_back(a, ptr);
            }
        }
    }

    return 0;
}