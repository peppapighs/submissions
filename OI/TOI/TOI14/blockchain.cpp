#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

int t, q;
pii pwr[1005];
map<pii, int> mp;

int main() {
    pwr[0] = pii(1, 1);
    for (int i = 1; i < 1005; i++)
        pwr[i] = pii(pwr[i - 1].x * 69, pwr[i - 1].y * 420);
    scanf("%d%d", &t, &q);
    while (t--) {
        int n;
        pii hsh(0, 0);
        scanf("%d", &n);
        for (int i = 1, a, b; i < n; i++) {
            scanf("%d%d", &a, &b);
            if (a > b)
                swap(a, b);
            hsh = pii(hsh.x + pwr[a].x, hsh.y + b + pwr[b].x);
        }
        mp[hsh]++;
    }
    while (q--) {
        int n;
        pii hsh(0, 0);
        scanf("%d", &n);
        for (int i = 1, a, b; i < n; i++) {
            scanf("%d%d", &a, &b);
            if (a > b)
                swap(a, b);
            hsh = pii(hsh.x + pwr[a].x, hsh.y + b + pwr[b].x);
        }
        printf("%d\n", mp[hsh]);
    }

    return 0;
}