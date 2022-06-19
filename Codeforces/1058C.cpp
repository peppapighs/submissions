#include <bits/stdc++.h>

using namespace std;

int n;
int qs[105];
char s[105];

int f(int l, int r) { return qs[r] - qs[l - 1]; }

int main() {
    scanf("%d", &n);
    scanf(" %s", s + 1);
    for (int i = 1; i <= n; i++)
        qs[i] += qs[i - 1] + s[i] - '0';
    for (int i = 1; i <= n; i++) {
        int k = i, x = qs[i];
        for (int j = i + 1; j <= n; j++) {
            if (j == n && qs[j] - qs[k] == x)
                return !printf("YES\n");
            if (qs[j] - qs[k] > x)
                break;
            if (j < n && s[j + 1] == '0')
                continue;
            if (qs[j] - qs[k] == x)
                k = j;
        }
    }
    printf("NO\n");

    return 0;
}