#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define x first
#define y second

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

//-----------------------------------------------------------

const int N = 1e4 + 5;

int freq[N];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        vector<int> val;
        memset(freq, 0, sizeof freq);
        scanf("%d", &n);
        for (int i = 1, a; i <= n; i++) {
            scanf("%d", &a);
            freq[a]++;
            if (freq[a] == 2)
                freq[a] = 0, val.emplace_back(a);
        }
        sort(val.begin(), val.end());
        double mn = 1e9;
        int a, b;
        for (int i = 0; i < val.size() - 1; i++) {
            double area = (double)(val[i] * val[i + 1]);
            double per = (double)(val[i] + val[i + 1]);
            if (per * per / area < mn)
                mn = per * per / area, a = val[i], b = val[i + 1];
        }
        printf("%d %d %d %d\n", a, a, b, b);
    }

    return 0;
}