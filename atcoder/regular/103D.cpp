#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e3 + 5;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
const char dir[4] = {'L', 'D', 'R', 'U'};

int n, X[N], Y[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d %d", X + i, Y + i);

    bool chk = (X[1] + Y[1]) & 1;
    for (int i = 2; i <= n; i++)
        if (((X[i] + Y[i]) & 1) != chk) {
            printf("-1\n");
            return 0;
        }
    if (!chk) {
        printf("32\n");
        printf("1 ");
        for (int i = 1; i <= n; i++)
            --X[i];
    } else
        printf("31\n");
    for (int i = 0; i <= 30; i++)
        printf("%d ", 1 << i);
    printf("\n");

    for (int i = 1; i <= n; i++) {
        long x = X[i], y = Y[i];
        vector<char> ans;
        for (int j = 30; ~j; j--) {
            long now = 1ll << j;
            for (int k = 0; k < 4; k++)
                if (abs(x + now * dx[k]) + abs(y + now * dy[k]) <= now - 1) {
                    x += now * dx[k], y += now * dy[k];
                    ans.emplace_back(dir[k]);
                    break;
                }
        }
        if (!chk)
            ans.emplace_back('R');
        reverse(ans.begin(), ans.end());
        for (char c : ans)
            printf("%c", c);
        printf("\n");
    }

    return 0;
}