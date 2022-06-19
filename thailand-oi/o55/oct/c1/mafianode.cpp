#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e6 + 5;

int n, l, r;
int deg[N];
priority_queue<pii> Q;

int main() {
    scanf("%d %d %d", &n, &l, &r);
    l += r;
    for (int i = 1; i <= n; i++)
        Q.emplace(0, i);

    while (l--) {
        char c;
        int a, b;
        scanf(" %c", &c);
        while (!Q.empty() && deg[Q.top().y] == -1)
            Q.pop();
        if (c == 'L') {
            scanf("%d %d", &a, &b);
            ++deg[b];
            Q.emplace(deg[b], b);
        } else if (c == 'C') {
            scanf("%d %d", &a, &b);
            deg[b] += 3;
            Q.emplace(deg[b], b);
        } else if (c == 'R')
            printf("%d\n", Q.top().y);
        else
            deg[Q.top().y] = -1;
    }

    return 0;
}
