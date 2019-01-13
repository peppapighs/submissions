#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int n;
vector<int> X = { -1 }, Y = { -1 };

int main() {
    scanf("%d", &n);
    for(int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        X.emplace_back(a), Y.emplace_back(b);
    }
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    printf("%d %d\n", X[(n+1)>>1], Y[(n+1)>>1]);

    return 0;
}