#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;
const int M = 1e9;

int n, m, k;
int dsu[N * 4];

int f(int x) { return n + m + x; }

int find(int x) { return dsu[x] = x == dsu[x] ? x : find(dsu[x]); }

void unite(int a, int b) { dsu[find(a)] = find(b); }

int main() {
    iota(dsu, dsu + N * 4, 0);
    scanf("%d %d %d", &n, &m, &k);

    for(int i = 1, a, b, c; i <= k; i++) {
        scanf("%d %d %d", &a, &b, &c);
        c ^= ((a % 2 == 0) && (b % 2 == 0));
        if(!c) unite(a, n + b), unite(f(a), f(n + b));
        else unite(a, f(n + b)), unite(f(a), n + b);
    }
    int cnt = 0;
    for(int i = 1; i <= n + m; i++) {
        if(find(i) == find(f(i))) return !printf("0\n");
        if(find(i) == i) ++cnt;
    }
    int ans = 1, mul = 2;
    for(--cnt; cnt; cnt >>= 1) {
        if(cnt & 1) ans = (1ll * ans * mul) % M;
        mul = (1ll * mul * mul) % M;
    } 
    printf("%d\n", ans);

    return 0;
}