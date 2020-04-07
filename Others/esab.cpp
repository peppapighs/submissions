#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

int n;

int ask(int i, int ret = 0) {
    printf("%d\n", i); fflush(stdout);
    scanf("%d", &ret);
    return ret;
}

void solve() {
    int sm = -1, df = -1;
    int l = 0, r = 0, t = 0;
    vector<int> V(n + 1);
    for(int i = 1, cnt = 0; cnt < n; i++) {
        if(i > 1 && i % 10 == 1) {
            ++i;
            int k;
            if(sm != -1 && df != -1) {
                k = ask(sm);
                if(k == V[sm]) {
                    k = ask(df);
                    if(k != V[df]) reverse(V.begin() + 1, V.end());
                } else {
                    for(int i = 1; i <= n; i++) V[i] ^= 1;
                    k = ask(df);
                    if(k != V[df]) reverse(V.begin() + 1, V.end());
                }
            } else {
                ask(1);
                if(sm != -1) {
                    k = ask(sm);
                    if(k != V[sm]) for(int i = 1; i <= n; i++) V[i] ^= 1;
                } else {
                    k = ask(df);
                    if(k != V[df]) reverse(V.begin() + 1, V.end());
                }
            }
        } else {
            if(t == 0) ++l, V[l] = ask(l);
            else {
                ++r, V[n - r + 1] = ask(n - r + 1);
                if(V[l] == V[n - r + 1]) sm = l;
                else df = l;
            }
            ++cnt;
            t ^= 1;
        }
    }
    for(int i = 1; i <= n; i++) printf("%d", V[i]);
    printf("\n");
    fflush(stdout);
    
    char c;
    scanf(" %c", &c);
}

int T;

int main() {
    scanf("%d %d", &T, &n);
    while(T--) solve();

    return 0;
}