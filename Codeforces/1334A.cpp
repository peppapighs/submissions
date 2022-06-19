#include <bits/stdc++.h>

using namespace std;

const int N = 105;

int n;
int a[N], b[N];

void solve() {
    scanf("%d", &n);
    bool valid = true;
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", a + i, b + i);
        if (b[i] > a[i])
            valid = false;
        if (i > 1) {
            if (a[i] < a[i - 1] || b[i] < b[i - 1])
                valid = false;
            if (a[i] - a[i - 1] < b[i] - b[i - 1])
                valid = false;
        }
    }
    if (valid)
        printf("YES\n");
    else
        printf("NO\n");
}

int T;

int main() {
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}