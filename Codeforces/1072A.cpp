#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define x first
#define y second

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

//-----------------------------------------------------------

int w, h, k;
int ans;

int main() {
    scanf("%d %d %d", &w, &h, &k);
    while (k--) {
        ans += (w * h) - (w - 2) * (h - 2);
        w -= 4, h -= 4;
    }
    printf("%d\n", ans);

    return 0;
}
