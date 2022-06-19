#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define x first
#define y second

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

//-----------------------------------------------------------

int main() {
    long long n, k;
    cin >> n >> k;
    long long d = k >> 1;
    if (n < k)
        d -= (k - n - 1);
    if (k % 2 == 0)
        d--;
    if (d < 0)
        printf("0");
    else
        printf("%lld", d);

    return 0;
}