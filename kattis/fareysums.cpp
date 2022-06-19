#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

int sieve[N], farey[N];

int phi(int n) {
    vector<int> factor;
    for (int x = n; x > 1; x /= sieve[x])
        factor.emplace_back(sieve[x]);
    reverse(factor.begin(), factor.end());
    factor.resize(unique(factor.begin(), factor.end()) - factor.begin());
    for (int &x : factor)
        n = n / x * (x - 1);
    return n;
}

int T, k, n;

int main() {
    for (int i = 2; i < N; i++)
        if (!sieve[i])
            for (int j = i; j < N; j += i)
                sieve[j] = i;

    farey[0] = 1, farey[1] = 2;
    for (int i = 2; i < N; i++)
        farey[i] = farey[i - 1] + phi(i);

    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &k, &n);
        int num = 3 * farey[n] - 4;
        if (num % 2 == 0)
            printf("%d %d\n", k, num / 2);
        else
            printf("%d %d/2\n", k, num);
    }

    return 0;
}