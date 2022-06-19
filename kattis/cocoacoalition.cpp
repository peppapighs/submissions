#include <bits/stdc++.h>

#define long long long

using namespace std;

long n, m, a;

int main() {
    scanf("%lld %lld %lld", &n, &m, &a);

    for (long now : vector<long>({a, n * m - a})) {
        if (now % n == 0 || now % m == 0)
            return !printf("1\n");
        for (long i = 1; i < n; i++)
            if (now % i == 0 && now / i <= m)
                return !printf("2\n");
    }
    printf("3\n");

    return 0;
}