#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int a1[n], a2[m];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a1[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &a2[i]);
    }
    int p1 = 0, p2 = 0;
    int ans = 0;
    while (p1 < n && p2 < m) {
        if (a1[p1] < a2[p2]) {
            p1++;
            a1[p1] += a1[p1 - 1];
        } else if (a1[p1] > a2[p2]) {
            p2++;
            a2[p2] += a2[p2 - 1];
        } else {
            ans++;
            p1++;
            p2++;
        }
    }

    printf("%d", ans);

    return 0;
}
