#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e9;
const int H = 5e8;

int ask(int x, int y) {
    // cerr << "ask " << x << " " << y << endl;
    char S[10];
    printf("%d %d\n", x, y), fflush(stdout);
    scanf(" %s", S);
    if (S[0] == 'M')
        return 0;
    if (S[0] == 'H')
        return 1;
    return 2;
}

void solve() {
    int x, y;
    for (int i = -H; i <= H; i += H)
        for (int j = -H; j <= H; j += H) {
            int now = ask(i, j);
            if (now == 2)
                return;
            if (now == 1)
                x = i, y = j;
        }
    // cerr << x << " " << y << endl;
    int lx, rx, ly, ry;
    int l = -N, r = x;
    while (l <= r) {
        int mid = (l + r) / 2;
        int now = ask(mid, y);
        if (now == 2)
            return;
        if (now == 1)
            lx = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    // cerr << lx << endl;
    l = x, r = N;
    while (l <= r) {
        int mid = (l + r) / 2;
        int now = ask(mid, y);
        if (now == 2)
            return;
        if (now == 1)
            rx = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    // cerr << rx << endl;
    l = -N, r = y;
    while (l <= r) {
        int mid = (l + r) / 2;
        int now = ask(x, mid);
        if (now == 2)
            return;
        if (now == 1)
            ly = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    l = y, r = N;
    while (l <= r) {
        int mid = (l + r) / 2;
        int now = ask(x, mid);
        if (now == 2)
            return;
        if (now == 1)
            ry = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    ask((lx + rx) / 2, (ly + ry) / 2);
}

int T, A, B;

int main() {
    scanf("%d %d %d", &T, &A, &B);
    while (T--)
        solve();

    return 0;
}