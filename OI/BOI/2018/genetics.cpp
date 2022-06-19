#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 4105;
const int P = 98765431;

int n, m, k;
long mpow[N], hsh[N][4];
char S[N][N];

int f(char c) {
    if (c == 'A')
        return 0;
    if (c == 'T')
        return 1;
    if (c == 'C')
        return 2;
    return 3;
}

int main() {
    mpow[0] = 1;
    for (int i = 1; i < N; i++)
        mpow[i] = mpow[i - 1] * P;

    scanf("%d %d %d", &n, &m, &k);
    long all = 0;
    for (int i = 1; i <= n; i++) {
        all += mpow[i];
        scanf(" %s", S[i] + 1);
        for (int j = 1; j <= m; j++)
            hsh[j][f(S[i][j])] += mpow[i];
    }
    for (int i = 1; i <= n; i++) {
        long sum = 0;
        for (int j = 1; j <= m; j++)
            sum += all - hsh[j][f(S[i][j])];
        if (all * k == sum + k * mpow[i])
            return !printf("%d\n", i);
    }

    return 0;
}