#include "bubblesort2.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

#define var int p = 1, int l = 0, int r = coord.size() - 1
#define mid ((l + r) >> 1)
#define lb p << 1, l, mid
#define rb p << 1 | 1, mid + 1, r

const int N = 1 << 20;

int n, q;
int t[N << 1], lz[N << 1];
vector<pii> coord;

int get(pii x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin();
}

void push(var) {
    if (lz[p]) {
        t[p] += lz[p];
        if (l != r)
            lz[p << 1] += lz[p], lz[p << 1 | 1] += lz[p];
        lz[p] = 0;
    }
}

void update(int x, int y, int k, var) {
    push(p, l, r);
    if (x > r || l > y)
        return;
    if (x <= l && r <= y) {
        lz[p] += k, push(p, l, r);
        return;
    }
    update(x, y, k, lb), update(x, y, k, rb);
    t[p] = max(t[p << 1], t[p << 1 | 1]);
}

vector<int> countScans(vector<int> A, vector<int> X, vector<int> V) {
    n = A.size(), q = X.size();

    for (int i = 0; i < n; i++)
        coord.emplace_back(A[i], i);
    for (int i = 0; i < q; i++)
        coord.emplace_back(V[i], X[i]);

    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    function<void(int, int)> add = [&](int i, int coef) {
        int idx1 = get(pii(A[i], i));
        update(idx1, idx1, (i + 1) * coef);
        int idx2 = get(pii(A[i], -1));
        update(idx2, coord.size() - 1, -coef);
    };

    vector<int> ans;
    for (int i = 0; i < n; i++)
        add(i, 1);
    for (int i = 0; i < q; i++) {
        add(X[i], -1);
        A[X[i]] = V[i];
        add(X[i], 1);
        ans.emplace_back(t[1]);
    }

    return ans;
}
