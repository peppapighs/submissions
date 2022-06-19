#include <bits/stdc++.h>

using namespace std;

bool read() {
    char S[15];
    scanf(" %s", S);
    return (S[0] == 'b');
}

int n;
bool st;
vector<int> B, W;

void push(int x, bool b) {
    if ((b == st) == st)
        B.emplace_back(x);
    else
        W.emplace_back(x);
}

int main() {
    scanf("%d", &n);
    printf("0 10\n");
    fflush(stdout);
    st = read();
    push(0, st);
    int l = 1, r = 1e9;
    for (int i = 2; i <= n; i++) {
        int m = (l + r) >> 1;
        printf("%d 10\n", m);
        fflush(stdout);
        bool b = read();
        push(m, b);
        if (b == st)
            l = m + 1;
        else
            r = m - 1;
    }
    sort(B.begin(), B.end());
    sort(W.begin(), W.end());
    int a, b;
    if (st) {
        a = B.back();
        if (W.empty()) {
            printf("%d 20 %d 0\n", a, a + 1);
            fflush(stdout);
        } else {
            b = W[0];
            printf("%d 20 %d 0\n", a, b);
            fflush(stdout);
        }
    } else {
        a = W.back();
        if (B.empty()) {
            printf("%d 20 %d 0\n", a, a + 1);
            fflush(stdout);
        } else {
            b = B[0];
            printf("%d 20 %d 0\n", a, b);
            fflush(stdout);
        }
    }

    return 0;
}
