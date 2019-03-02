#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

struct item {
    int A[10];

    item() { for(int i = 0; i < 10; i++) A[i] = i; }

    friend item operator+(const item &a, const item &b) {
        item ret;
        for(int i = 0; i < 10; i++) ret.A[i] = b.A[a.A[i]];
        return ret;
    }
};

const int N = 3e5+5;;

int n, q;
int pos[N];
item iden;
item t[N<<1];
vector<int> coord;
vector<pii> Q;
vector<pair<int, item> > V;

int get(int x) { return lower_bound(coord.begin(), coord.end(), x) - coord.begin(); }

void update(int x, item k) {
    for(t[x += N] = k; x != 1; x >>= 1) {
        if(x & 1) t[x>>1] = t[x^1] + t[x];
        else t[x>>1] = t[x] + t[x^1];
    }
}

int main() {
    V.emplace_back(-1, iden);
    scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; i++) {
        int a; item now;
        scanf("%d", &a);
        for(int j = 0; j < 10; j++) scanf("%d", &now.A[j]);
        coord.emplace_back(a);
        V.emplace_back(a, now);
    }
    for(int i = 1, a, b; i <= q; i++) {
        scanf("%d %d", &a, &b);
        coord.emplace_back(b);
        Q.emplace_back(a, b);
    }
    sort(coord.begin(), coord.end());
    coord.erase(unique(coord.begin(), coord.end()), coord.end());
    for(int i = 1; i <= n; i++) {
        pos[i] = get(V[i].x);
        update(pos[i], V[i].y);
    }
    for(pii q : Q) {
        item now = t[N + pos[q.x]];
        update(pos[q.x], iden);
        pos[q.x] = get(q.y);
        update(pos[q.x], now);
        printf("%d\n", t[1].A[0]);
    }

    return 0;
}