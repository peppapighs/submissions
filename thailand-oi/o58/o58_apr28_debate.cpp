#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 7e4+5;

struct node {
    pii d;
    node *l, *r;
    node(pii d, node *l, node *r) : d(d), l(l), r(r) { }
    node(pii d) : d(d), l(nullptr), r(nullptr) { }
};

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
node* newleaf(pii d) { return new node(d); }
node* newpar(node* l, node* r) { return new node(add(l->d, r->d), l, r); }

int n, q, e, pos[N];
long A[N], pref[N];
node* ver[N];

node* build(int l = 1, int r = n) {
    if(l == r) return newleaf(pii(0, 0));
    int mid = (l + r) >> 1;
    return newpar(build(l, mid), build(mid+1, r));
}

node* update(int x, pii k, node* p, int l = 1, int r = n) {
    if(l == r) return newleaf(k);
    int mid = (l + r) >> 1;
    if(x <= mid) return newpar(update(x, k, p->l, l, mid), p->r);
    else return newpar(p->l, update(x, k, p->r, mid+1, r));
}

pii query(int x, int y, node* p, int l = 1, int r = n) {
    if(x > r || l > y) return pii(0, 0);
    if(x <= l && r <= y) return p->d;
    int mid = (l + r) >> 1;
    return add(query(x, y, p->l, l, mid), query(x, y, p->r, mid+1, r)); 
}

int main() {
    iota(pos, pos+N, 0);
    scanf("%d %d %d", &n, &q, &e);
    for(int i = 1; i <= n; i++) scanf("%lld", A+i);
    for(int i = 1; i <= n; i++) pref[i] = A[i] + pref[i-1];
    sort(pos+1, pos+n+1, [&](const int &a, const int &b) {
        return A[a] > A[b];
    });
    ver[0] = build();
    for(int i = 1; i <= n; i++) ver[i] = update(pos[i], pii(A[pos[i]], 1), ver[i-1]);
    for(int i = 1, a, b, prev = 0; i <= q; i++) {
        scanf("%d %d", &a, &b);
        if(e) a ^= prev, b ^= prev;
        int l = 1, r = n;
        while(l < r) {
            int mid = (l + r) >> 1;
            if(query(a, b, ver[mid]).y >= (b - a + 1) / 2) r = mid;
            else l = mid + 1;
        }
        long ans = 2ll * query(a, b, ver[r]).x - (pref[b] - pref[a-1]);
        printf("%lld\n", ans);
        prev = (int)ans;
    }

    return 0;
}