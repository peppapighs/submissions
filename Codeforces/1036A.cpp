#include <bits/stdc++.h>

using namespace std;

long long a, b;

int main() {
    scanf("%lld %lld", &a, &b);
    printf("%lld\n", b / a + (b % a ? 1 : 0));

    return 0;
}