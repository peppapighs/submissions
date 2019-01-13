#include <bits/stdc++.h>

using namespace std;

const int N = 1<<17;

int n, m;
int H[N], P[N], cur[N], lz[N<<1];
int id[N], t[N+1], ans[N];

void update(int x, int k) { for(int i = x; i; i -= i & -i) t[i] += k; }

int get(int x) {
        int ret = 0;
        for(int i = x; i < N; i += i & -i) ret += t[i];
        return ret;
}

void push(int p, int l, int r) {
        if(lz[p] != -1) {
                if(l != r) lz[p<<1] = lz[p<<1|1] = lz[p];
                else cur[l] = lz[p];
                lz[p] = -1;
        }
}

int query(int x, int p = 1, int l = 1, int r = m) {
        push(p, l, r);
        if(l == r) return cur[l] + P[l];
        int m = (l + r) >> 1;
        if(x <= m) return query(x, p<<1, l, m);
        else return query(x, p<<1|1, m+1, r);
}

void lazy(int x, int y, int k, int p = 1, int l = 1, int r = m) {
        push(p, l, r);
        if(x > r || l > y) return;
        if(x <= l && r <= y) {
                lz[p] = k;
                push(p, l, r);
                return;
        }
        int m = (l + r) >> 1;
        lazy(x, y, k, p<<1, l, m), lazy(x, y, k, p<<1|1, m+1, r);
}

int main() {
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; i++) scanf("%d", H+i);
        for(int i = 1; i <= m; i++) scanf("%d", P+i), id[i] = i;
        sort(id+1, id+m+1, [&](const int &a, const int &b) {
                return P[a] < P[b];
        });
        sort(P+1, P+m+1);
        fill_n(cur, N, H[1]);
        memset(lz, -1, sizeof lz);
        for(int i = 2; i <= n; i++) {
                int l = 1, r = n;
                while(l < r) {
                        int m = (l + r) >> 1;
                        if(query(m) >= H[i]) r = m;
                        else l = m+1;
                }
                update(r-1, 1);
                lazy(r, n, H[i]);
        }
        for(int i = 1; i <= m; i++) ans[id[i]] = get(i);
        for(int i = 1; i <= m; i++) printf("%d\n", ans[i]);

        return 0;
}
