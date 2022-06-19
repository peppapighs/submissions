#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

int n;
long long ans;
deque<pii> Q;

int main() {
    scanf("%d", &n);
    for (int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        pii x(a, 1);
        // for(pii z : Q) printf("(%d %d), ", z.x, z.y);
        // printf("\n");
        while (!Q.empty() && Q.back().x <= a) {
            ans += Q.back().y;
            if (Q.back().x == a)
                x.y += Q.back().y;
            Q.pop_back();
        }
        if (!Q.empty())
            ans++;
        Q.push_back(x);
    }

    printf("%lld", ans);

    return 0;
}