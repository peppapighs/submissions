#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define pii pair<int, int>

using namespace std;

const int N = 1e5 + 5;

int n, m, k;
int ans[N], t[N + 1];
vector<iii> rect[N];
vector<pii> query[N];

void update(int x, int k) {
    for (int i = x + 1; i < N; i += i & -i)
        t[i] += k;
}

int get(int x) {
    int ret = 0;
    for (int i = x + 1; i; i -= i & -i)
        ret += t[i];
    return ret;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1, a, b, c, d; i <= n; i++) {
        scanf("%d %d %d %d", &a, &b, &c, &d);
        if (a > c)
            swap(a, c);
        if (b > d)
            swap(b, d);
        rect[a].emplace_back(b, d, 1);
        rect[c + 1].emplace_back(b, d, -1);
    }
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        query[a].emplace_back(b, i);
    }
    for (int x = 0; x < N; x++) {
        for (iii rec : rect[x]) {
            int y1, y2, c;
            tie(y1, y2, c) = rec;
            update(y1, c), update(y2 + 1, -c);
        }
        for (pii que : query[x]) {
            int y, id;
            tie(y, id) = que;
            ans[id] = get(y);
        }
    }
    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);

    return 0;
}
