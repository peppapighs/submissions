#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5+5;

int n, q;
int price[N], a[N], b[N];
set<pii> S[4];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", price + i);
    for(int i = 1; i <= n; i++) scanf("%d", a + i);
    for(int i = 1; i <= n; i++) scanf("%d", b + i);

    for(int i = 1; i <= n; i++) {
        S[a[i]].emplace(price[i], i);
        if(a[i] != b[i]) S[b[i]].emplace(price[i], i);
    }
    scanf("%d", &q);
    while(q--) {
        int c;
        scanf("%d", &c);
        if(S[c].empty()) printf("-1 ");
        else {
            pii p = *S[c].begin();
            printf("%d ", p.x);
            S[a[p.y]].erase(p);
            S[b[p.y]].erase(p);
        }
    }
    printf("\n");

    return 0;
}