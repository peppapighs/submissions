#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int n;
char ans[N];

void solve(int idx) {
    memset(ans, 0, sizeof ans);

    scanf("%d", &n);
    vector<array<int, 3> > V;
    for(int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        V.push_back({a, b, i-1});
    }
    sort(V.begin(), V.end(), [&](array<int, 3> a, array<int, 3> b) {
        return a[0] < b[0];
    });
    int pre = -1, cnt = 0;
    for(int i = 0; i < n; i++) if(pre == -1 || V[i][0] >= pre) 
        ans[V[i][2]] = 'C', pre = V[i][1], ++cnt;
    pre = -1;
    for(int i = 0; i < n; i++) if(!ans[V[i][2]] && (pre == -1 || V[i][0] >= pre))
        ans[V[i][2]] = 'J', pre = V[i][1], ++cnt;

    printf("Case #%d: ", idx);
    if(cnt != n) printf("IMPOSSIBLE\n");
    else printf("%s\n", ans);
}

int T;

int main() {
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) solve(i);

    return 0;
}