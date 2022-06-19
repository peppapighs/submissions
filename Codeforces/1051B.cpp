#include <bits/stdc++.h>
using namespace std;

#define long long long

int main() {
    long a, b;
    cin >> a >> b;
    puts("YES");
    for (; a < b; a += 2)
        printf("%lld %lld\n", a, a + 1);
}