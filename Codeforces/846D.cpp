#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, k, q;
    scanf("%d%d%d%d", &n, &m, &k, &q);
    pair<int, pair<int, int>> pixel[q];
    for (int i = 0; i < q; i++) {
        int x, y, t;
        scanf("%d%d%d", &x, &y, &t);
        pixel[i] = {t, {x, y}};
    }

    sort(pixel, pixel + q);

    int low = 0, high = q - 1;
    int res = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        bool f = false;
        vector<vector<int>> mx(n + 1, vector<int>(m + 1, 0));
        vector<vector<int>> psum(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i <= mid; i++) {
            mx[pixel[i].second.first][pixel[i].second.second] = 1;
        }
        for (int j = 1; j <= m; j++) {
            for (int i = 1; i <= n; i++) {
                psum[i][j] = psum[i - 1][j] + psum[i][j - 1] -
                             psum[i - 1][j - 1] + mx[i][j];
            }
        }
        for (int j = k; j <= m; j++) {
            for (int i = k; i <= n; i++) {
                if ((psum[i][j] - psum[i - k][j] - psum[i][j - k] +
                     psum[i - k][j - k]) == k * k) {
                    f = true;
                }
            }
        }
        if (f) {
            res = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if (res == -1) {
        printf("-1");
        return 0;
    }

    printf("%d", pixel[res].first);

    return 0;
}
