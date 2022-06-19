#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;
const long iden = 98765431;

struct node {
    pii d;
    node *l, *r;
    node(pii d, node *l, node *r) : d(d), l(l), r(r) {}
};

long f(int l, int r) {
    return 1ll * r * (r + 1) / 2ll - 1ll * l * (l - 1) / 2ll;
}
pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
node *newleaf(pii d) { return new node(d, nullptr, nullptr); }
node *newpar(node *l, node *r) { return new node(add(l->d, r->d), l, r); }

int n, q;
long hsh1[N], hsh2[N], mpow[N];
long cnt[2][N];
char A[N];
node *t[4][N];
vector<long> vec[4];

long g(int i, int x) {
    if (i == 0)
        return cnt[0][x] - x;
    if (i == 1)
        return cnt[0][x] + x;
    if (i == 2)
        return cnt[1][x] - x;
    return cnt[1][x] + x;
}

node *build(int l = 1, int r = n) {
    if (l == r)
        return newleaf(pii(0, 0));
    int mid = (l + r) >> 1;
    return newpar(build(l, mid), build(mid + 1, r));
}

node *update(int x, pii k, node *p, int l = 1, int r = n) {
    if (l == r)
        return newleaf(add(p->d, k));
    int mid = (l + r) >> 1;
    if (x <= mid)
        return newpar(update(x, k, p->l, l, mid), p->r);
    else
        return newpar(p->l, update(x, k, p->r, mid + 1, r));
}

pii query(node *p1, node *p2, long x, int i, int l = 1, int r = n) {
    if (1 > r || vec[i][l - 1] > x)
        return pii(0, 0);
    if (1 <= l && vec[i][r - 1] <= x)
        return sub(p2->d, p1->d);
    int mid = (l + r) >> 1;
    return add(query(p1->l, p2->l, x, i, l, mid),
               query(p1->r, p2->r, x, i, mid + 1, r));
}

void count_palindrome() {
    mpow[0] = 1;
    for (int i = 1; i <= n; i++)
        hsh1[i] = hsh1[i - 1] * iden + A[i], mpow[i] = mpow[i - 1] * iden;
    for (int i = n; i; i--)
        hsh2[i] = hsh2[i + 1] * iden + A[i];
    for (int i = 1; i <= n; i++) {
        int l = 1, r = min(i, n - i + 1);
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            long lhs = hsh2[i - mid + 1] - hsh2[i + 1] * mpow[mid];
            long rhs = hsh1[i + mid - 1] - hsh1[i - 1] * mpow[mid];
            if (lhs == rhs)
                l = mid;
            else
                r = mid - 1;
        }
        cnt[0][i] = l;
        if (i == n || A[i] != A[i + 1])
            continue;
        l = 1, r = min(i, n - i);
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            long lhs = hsh2[i - mid + 1] - hsh2[i + 1] * mpow[mid];
            long rhs = hsh1[i + mid] - hsh1[i] * mpow[mid];
            if (lhs == rhs)
                l = mid;
            else
                r = mid - 1;
        }
        cnt[1][i + 1] = l;
    }
}

int get(int i, long x) {
    return lower_bound(vec[i].begin(), vec[i].end(), x) - vec[i].begin() + 1;
}

void coord_compress() {
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 4; j++)
            vec[j].emplace_back(g(j, i));
    for (int i = 0; i < 4; i++)
        sort(vec[i].begin(), vec[i].end());
    t[0][0] = t[1][0] = t[2][0] = t[3][0] = build();
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 4; j++)
            t[j][i] = update(get(j, g(j, i)), pii(g(j, i), 1), t[j][i - 1]);
}

long calc(int a, int b, int l, int r) {
    int mid = (l + r) >> 1;
    pii lhs = query(t[a][l - 1], t[a][mid], 1 - l, a);
    pii rhs = query(t[b][mid], t[b][r], r + 1, b);
    long now = f(l, mid) - f(mid + 1, r) + lhs.x + rhs.x;
    now += 1ll * (1 - l) * (mid - l + 1 - lhs.y);
    now += 1ll * (r + 1) * (r - mid - rhs.y);
    return now;
}

int main() {
    scanf("%d %s", &n, A + 1);
    count_palindrome();
    coord_compress();
    scanf("%d", &q);
    for (int i = 1, l, r; i <= q; i++) {
        scanf("%d %d", &l, &r);
        printf("%lld\n", calc(0, 1, l, r) + calc(2, 3, l + 1, r));
    }

    return 0;
}