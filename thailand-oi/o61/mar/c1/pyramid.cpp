#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e4 + 5;

int n;
int t[N][N];
vector<int> X, Y;
vector<pii> Q;

void update(int x, int y) {
    for (int i = x + 1; i < N; i += i & (-i))
        for (int j = y + 1; j; j -= j & (-j))
            t[i][j]++;
}

int sum(int x, int y) {
    int ret = 0;
    for (int i = x + 1; i; i -= i & (-i))
        for (int j = y + 1; j < N; j += j & (-j))
            ret += t[i][j];
    return ret;
}

int getX(int x) { return lower_bound(X.begin(), X.end(), x) - X.begin(); }
int getY(int x) { return lower_bound(Y.begin(), Y.end(), x) - Y.begin(); }

int main() {
    scanf("%d", &n);
    while (n--) {
        int x, h;
        scanf("%d %d", &x, &h);
        X.emplace_back(x - h);
        Y.emplace_back(x + h);
        Q.emplace_back(x - h, x + h);
    }
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    X.erase(unique(X.begin(), X.end()), X.end());
    Y.erase(unique(Y.begin(), Y.end()), Y.end());
    for (pii q : Q) {
        printf("%d\n", sum(getX(q.x), getY(q.y)));
        update(getX(q.x), getY(q.y));
    }

    return 0;
}