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
    long long n, q;
    cin >> n >> q;
    while (q--) {
        long long x, y;
        cin >> x >> y;
        long long t = (x - 1) * n + y;
        if ((x + y) & 1) {
            printf("%lld\n", (n * n + 1) / 2 + (t + 1) / 2);
        } else {
            printf("%lld\n", (t + 1) / 2);
        }
    }

    return 0;
}