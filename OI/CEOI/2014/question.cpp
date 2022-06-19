#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;

int n, T;
vector<int> vec = {0};

void A() {
    scanf("%d %d", &n, &T);
    for (int t = 1, a, b; t <= T; t++) {
        scanf("%d %d", &a, &b);
        a = vec[a], b = vec[b];
        for (int i = 1; i <= 12; i++)
            if ((a >> (i - 1) & 1) && !(b >> (i - 1) & 1)) {
                printf("%d\n", i);
                break;
            }
    }
}

void B() {
    scanf("%d %d", &n, &T);
    for (int t = 1, a, b; t <= T; t++) {
        scanf("%d %d", &a, &b);
        a = vec[a];
        if (a >> (b - 1) & 1)
            printf("yes\n");
        else
            printf("no\n");
    }
}

int main() {
    for (int i = 0; i < (1 << 12); i++)
        if (__builtin_popcount(i) == 6)
            vec.emplace_back(i);

    scanf("%d", &n);
    n == 1 ? A() : B();

    return 0;
}