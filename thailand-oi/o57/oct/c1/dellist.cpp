#include <bits/stdc++.h>

#define pil pair<int, llist *>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

struct llist {
    int val;
    llist *l, *r;
    llist() {}
    llist(int val) : val(val), l(NULL), r(NULL) {}
    llist(int val, llist *l, llist *r) : val(val), l(l), r(r) {}
};

int k, m;
int par[N];
map<int, vector<pil>> book;
llist *H[N], *T[N];

int find(int i) { return par[i] = i == par[i] ? i : find(par[i]); }

void insert(int a, int i) {
    llist *node = new llist(a);
    book[a].emplace_back(i, node);
    if (H[i] == NULL) {
        H[i] = node, T[i] = node;
    } else {
        node->l = T[i];
        T[i]->r = node;
        T[i] = node;
    }
}

void del(int i, int v) {
    if (!book.count(v))
        return;
    for (pil &p : book[v]) {
        if (find(p.x) != i)
            continue;
        p.x = 0;
        llist *node = p.y;
        if (node->l != NULL)
            node->l->r = node->r;
        if (node->r != NULL)
            node->r->l = node->l;
        if (node == H[i])
            H[i] = node->r;
        if (node == T[i])
            T[i] = node->l;
    }
}

void merge(int i, int j) {
    if (H[j] == NULL)
        return;
    else
        H[j]->l = T[i];
    if (T[i] != NULL) {
        T[i]->r = H[j];
        T[i] = T[j];
    } else {
        H[i] = H[j];
        T[i] = T[j];
    }
    H[j] = T[j] = NULL;
}

int main() {
    scanf("%d%d", &k, &m);
    for (int i = 1; i <= k; i++) {
        par[i] = i;
        int n;
        scanf("%d", &n);
        while (n--) {
            int a;
            scanf("%d", &a);
            insert(a, i);
        }
    }
    while (m--) {
        int t;
        scanf("%d", &t);
        if (t == 1) {
            int i, v;
            scanf("%d%d", &i, &v);
            del(i, v);
        } else if (t == 2) {
            int i, j;
            scanf("%d%d", &i, &j);
            int hi = find(i), hj = find(j);
            par[hj] = hi;
            merge(i, j);
        }
    }
    for (int i = 1; i <= k; i++)
        for (llist *cur = H[i]; cur != NULL; cur = cur->r)
            printf("%d\n", cur->val);

    return 0;
}
