#include <bits/stdc++.h>

using namespace std;

const int N = 105;

int T, n;
char s[N];

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %s", &n, s + 1);
        int e = -1;
        for (int i = 1; i <= n; i++)
            if (s[i] == '8') {
                e = i;
                break;
            }
        if (e == -1 || n - e < 10)
            printf("NO\n");
        else
            printf("YES\n");
    }

    return 0;
}