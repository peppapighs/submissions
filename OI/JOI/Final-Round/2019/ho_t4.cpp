#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;

int n, cnt[3][N];
long ans;
queue<int> pos[3], coin[3];

int main() {
    scanf("%d", &n);
    for (int i = 1, x, y; i <= 2 * n; i++) {
        scanf("%d %d", &x, &y);
        if (x < 1)
            ans += abs(x - 1), x = 1;
        if (x > n)
            ans += abs(x - n), x = n;
        if (y < 1)
            ans += abs(y - 1), y = 1;
        if (y > 2)
            ans += abs(y - 2), y = 2;
        ++cnt[y][x];
    }
    for (int i = 1; i <= n; i++) {
        pos[1].emplace(i), pos[2].emplace(i);
        for (int j = 1; j <= 2; j++)
            while (cnt[j][i]--)
                coin[j].emplace(i);
        for (int j = 1; j <= 2; j++)
            while (!pos[j].empty() && !coin[j].empty()) {
                ans += abs(pos[j].front() - coin[j].front());
                pos[j].pop(), coin[j].pop();
            }
        for (int j = 1; j <= 2; j++)
            while (!pos[j ^ 3].empty() && !coin[j].empty()) {
                ans += abs(pos[j ^ 3].front() - coin[j].front()) + 1;
                pos[j ^ 3].pop(), coin[j].pop();
            }
    }
    printf("%lld\n", ans);

    return 0;
}