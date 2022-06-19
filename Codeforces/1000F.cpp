#include <bits/stdc++.h>

#define ii pair<int, int>

using namespace std;

const int N = 5e5 + 5;
const int M = 1 << 19;

ii tree[M << 1];
vector<vector<ii>> que(N);
int n, m, arr[N], ans[N], pos[N];

void update(int x, int a, int b, int p = 1, int l = 1, int r = n) {
    if (l == r)
        return void(tree[p] = {a, b});
    int mid = (l + r) >> 1;
    if (x <= mid)
        update(x, a, b, p << 1, l, mid);
    else
        update(x, a, b, p << 1 | 1, mid + 1, r);
    tree[p] = min(tree[p << 1], tree[p << 1 | 1]);
}

ii query(int x, int y, int p = 1, int l = 1, int r = n) {
    if (x > r || l > y)
        return {INT_MAX, -1};
    if (x <= l && r <= y)
        return tree[p];
    int mid = (l + r) >> 1;
    return min(query(x, y, p << 1, l, mid),
               query(x, y, p << 1 | 1, mid + 1, r));
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    scanf("%d", &m);
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d%d", &a, &b);
        que[b].emplace_back(a, i);
    }
    for (int i = 1; i <= n; i++) {
        if (pos[arr[i]])
            update(pos[arr[i]], INT_MAX, -1);
        update(i, pos[arr[i]], arr[i]);
        pos[arr[i]] = i;
        for (ii q : que[i]) {
            ii mn = query(q.first, i);
            if (mn.first < q.first)
                ans[q.second] = mn.second;
        }
    }

    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);

    return 0;
}