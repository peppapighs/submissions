#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, w;
    scanf("%d%d", &n, &w);
    int cnt = 0;
    int l = 0, r = w;
    while (n--) {
        int a;
        scanf("%d", &a);
        if (abs(a) > w) {
            printf("0");
            return 0;
        }
        cnt += a;
        if (cnt > w || -cnt > w) {
            printf("0");
            return 0;
        }
        if (cnt < 0) {
            l = max(l, abs(cnt));
        } else {
            r = min(r, w - cnt);
        }
    }
    if (l <= r) {
        printf("%d", r - l + 1);
    } else {
        printf("0");
    }

    return 0;
}
