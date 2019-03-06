#include <bits/stdc++.h>

#define long long long

using namespace std;

long a, b, c, d;

int main() {
    scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
    if(a != d || (c != 0 && !a)) return !printf("0\n");
    printf("1\n");

    return 0;
}
