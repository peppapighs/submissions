#include <bits/stdc++.h>

using namespace std;

const int N = 2e3+5;

int h, w, mn, mx;
int A[N][N], ans = 1e9;

void solve() {
    int l = 0, r = mx - mn;
    while(l <= r) {
        int mid = (l + r) >> 1;
        int pos = 0, valid = 1;
        for(int i = 1; i <= h; i++) {
            for(int j = 1; j <= w; j++) if(mx - A[i][j] > mid)
                pos = max(pos, j);
            for(int j = 1; j <= w; j++) if(A[i][j] - mn > mid)
                if(j <= pos) valid = 0;
        }
        if(valid) r = mid - 1, ans = min(ans, mid);
        else l = mid + 1;
    }
}

void flip_col() {
    for(int i = 1; i <= h; i++)
        for(int j = 1; j <= w / 2; j++)
            swap(A[i][j], A[i][w - j + 1]);
}

void flip_row() {
    for(int j = 1; j <= w; j++)
        for(int i = 1; i <= h / 2; i++)
            swap(A[i][j], A[h - i + 1][j]);
}

int main() {
    scanf("%d %d", &h, &w);
    mn = 1e9, mx = -1e9;
    for(int i = 1; i <= h; i++) for(int j = 1; j <= w; j++) {
        scanf("%d", A[i] + j);
        mn = min(mn, A[i][j]);
        mx = max(mx, A[i][j]);
    }
    solve();
    flip_col(), solve();
    flip_row(), solve();
    flip_col(), solve();
    printf("%d\n", ans);

    return 0;
}