#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e4 + 5;

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

int n;
int A[N];
pii id(69, 420);

int g(int x) { return (x + n) % n; }

bool f(int m) {
    pii w(0, 0), h(1, 1);
    set<pii> found;
    for (int i = 0; i < m; i++) {
        w = add(mul(w, id), pii(A[i], A[i]));
        h = mul(h, id);
    }
    found.emplace(w);
    for (int i = m; i < n + m - 1; i++) {
        w = add(mul(w, id), pii(A[g(i)], A[g(i)]));
        w = sub(w, mul(pii(A[i - m], A[i - m]), h));
        if (found.find(w) != found.end())
            return true;
        found.emplace(w);
    }
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", A + i);
    int l = 0, r = n;
    while (l < r) {
        int m = (l + r + 1) >> 1;
        if (f(m))
            l = m;
        else
            r = m - 1;
    }
    if (l == n)
        printf("-1\n");
    else
        printf("%d\n", l);

    return 0;
}
