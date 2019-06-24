#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5+5;
const long iden = 98765431;

long hsh1[N], hsh2[N], hpow[N];

long gethsh1(int a, int b) {
    long ret = hsh1[b];
    long sub = hsh1[a-1] * hpow[b - a + 1];
    return ret - sub;
}

long gethsh2(int a, int b) {
    long ret = hsh2[b];
    long sub = hsh2[a-1] * hpow[b - a + 1];
    return ret - sub;
}

int n, m, a[N], b[N];
vector<pii> v;

int main() {
    hpow[0] = 1;
    for(int i = 1; i < N; i++) hpow[i] = hpow[i-1] * iden;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%d", a+i);
        hsh1[i] = hsh1[i-1] * iden + a[i];
    }
    for(int i = 1; i <= m; i++) {
        scanf("%d", b+i);
        hsh2[i] = hsh2[i-1] * iden + b[i];

        if(b[i] == 1) continue;
        if(v.empty() || (i > 1 && b[i-1] == 1)) v.emplace_back(i, i);
        else ++v.back().y;
    }
    int ans = 0;
    for(int i = 1, j = m; j <= n; i++, j++) {
        bool valid = true;
        for(pii p : v) {
            long lhs = gethsh1(p.x + i - 1, p.y + i - 1);
            long rhs = gethsh2(p.x, p.y);
            if(lhs != rhs) valid = false;
        }
        if(valid) ++ans;
    }
    printf("%d\n", ans);

    return 0;
}