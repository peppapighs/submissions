#include <bits/stdc++.h>

using namespace std;

int ask(int x, int ret = 0) {
    printf("Q %d\n", x);
    fflush(stdout);
    scanf("%d", &ret);
    return ret;
}

int main() {
    int l = 0, r = 1e6;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (ask(mid))
            l = mid;
        else
            r = mid - 1;
    }
    int trail = l;
    l = 5, r = 1e5;
    while (l < r) {
        int mid = (l + r) >> 1;
        int base = 5, cnt = 0;
        while (base <= mid) {
            cnt += mid / base;
            base *= 5;
        }
        if (cnt >= trail)
            r = mid;
        else
            l = mid + 1;
    }
    printf("A %d\n", r);
    fflush(stdout);

    return 0;
}