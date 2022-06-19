#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n;
int A[N][2], mn[N][2], mx[N][2];

int main() {
    scanf("%d", &n), n <<= 1;
    for (int j = 0; j < 2; j++)
        for (int i = 1; i <= n; i++)
            scanf("%d", &A[i][j]);
    for (int i = 1; i <= n; i++) {
        mn[i][0] = mn[i][1] = 1e9, mx[i][0] = mx[i][1] = -1e9;
        for (int x = 0; x < 2; x++)
            for (int y = 0; y < 2; y++) {
                if (A[i - 1][y] > A[i][x])
                    continue;
                int pre_mn = mn[i - 1][y] + (x == 0);
                int pre_mx = mx[i - 1][y] + (x == 0);
                mn[i][x] = min(mn[i][x], pre_mn),
                mx[i][x] = max(mx[i][x], pre_mx);
            }
    }

    int cnt = n / 2;
    vector<int> ans;

    if (mn[n][0] <= n / 2 && n / 2 <= mx[n][0])
        ans.emplace_back(0), --cnt;
    else if (mn[n][1] <= n / 2 && n / 2 <= mx[n][1])
        ans.emplace_back(1);
    else
        return !printf("-1\n");

    for (int i = n - 1; i; i--)
        for (int j = 0; j < 2; j++) {
            if (A[i][j] > A[i + 1][ans.back()])
                continue;
            if (mn[i][j] <= cnt && cnt <= mx[i][j]) {
                cnt -= (j == 0);
                ans.emplace_back(j);
                break;
            }
        }
    reverse(ans.begin(), ans.end());
    for (int x : ans)
        printf("%c", 'A' + x);
    printf("\n");

    return 0;
}