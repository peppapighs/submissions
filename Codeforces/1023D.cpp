#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define x first
#define y second

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

//-----------------------------------------------------------

const int N = 1 << 19;

int INF = (int)1e9;

int n, q;
int t[N << 1];
int A[N];
vector<int> need;
int last[N];

void build(int p = 1, int l = 1, int r = n) {
    if (l == r)
        return void(t[p] = A[l]);
    int mid = (l + r) >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
    t[p] = min(t[p << 1], t[p << 1 | 1]);
}

int query(int x, int y, int p = 1, int l = 1, int r = n) {
    if (x > r || l > y)
        return INT_MAX;
    if (x <= l && r <= y)
        return t[p];
    int mid = (l + r) >> 1;
    return min(query(x, y, p << 1, l, mid),
               query(x, y, p << 1 | 1, mid + 1, r));
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);
        if (!A[i]) {
            need.emplace_back(i);
            A[i] = INF;
        }
    }
    build();
    bool valid = false;
    for (int i = 1; i <= n; i++) {
        if (A[i] == INF)
            continue;
        if (A[i] == q)
            valid = true;
        if (last[A[i]] && query(last[A[i]], i) < A[i])
            return !printf("NO\n");
        last[A[i]] = i;
    }
    if (!valid && need.empty())
        return !printf("NO\n");
    printf("YES\n");
    for (int p : need) {
        if (!valid)
            A[p] = q, valid = true;
        else {
            if (p == 1)
                A[p] = 1;
            else
                A[p] = A[p - 1];
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", A[i]);

    return 0;
}