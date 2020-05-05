#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, m, C[N];
pii A[N];

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d %d", &A[i].y, &A[i].x);
    for(int i = 1; i <= m; i++) scanf("%d", C + i);

    sort(A + 1, A + n + 1, greater<pii>());
    sort(C + 1, C + m + 1, greater<int>());

    int ptr = 1, ans = 0;
    for(int i = 1; i <= m; i++) {
        while(ptr <= n && A[ptr].y > C[i]) ++ptr;
        if(ptr <= n) ++ans, ++ptr;
    }
    printf("%d\n", ans);

    return 0;
}