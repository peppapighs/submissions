#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1 << 7;
const int M = 1e3 + 5;

int n, m;
__int128 g[N], clique[M];

__int128 mask(int i) { return (__int128)1 << i; }

int main() {
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 0, a, b; i < m; i++) {
            scanf("%d %d", &a, &b);
            --a, --b;
            g[a] |= mask(b);
            g[b] |= mask(a);
        }
        int ptr = 0;
        for (int i = 0; i < n && ptr < 1000; i++) {
            if (i == 0)
                clique[ptr] |= mask(i);
            else {
                for (int j = 0; j <= ptr && ptr < 1000; j++) {
                    clique[ptr + 1] = clique[j] & g[i];
                    if (clique[ptr + 1] == clique[j])
                        clique[j] |= mask(i);
                    else {
                        clique[ptr + 1] |= mask(i);
                        bool ok = true;
                        for (int k = 0; k <= ptr; k++)
                            ok &= (clique[k] != clique[ptr + 1]);
                        for (int k = 0; k < i; k++)
                            ok &= ((clique[ptr + 1] & g[k]) != clique[ptr + 1]);
                        if (ok)
                            ++ptr;
                    }
                }
            }
        }
        if (ptr < 1000)
            printf("%d\n", ptr + 1);
        else
            printf("Too many maximal sets of friends.\n");

        for (int i = 0; i < N; i++)
            g[i] = 0;
        for (int i = 0; i < M; i++)
            clique[i] = 0;
    }

    return 0;
}