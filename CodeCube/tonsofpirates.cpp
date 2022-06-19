#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

int n, q;
int t[N];
vector<int> V;
vector<pii> Q;
vector<string> S = {"sleep", "eat", "work", "eat", "work", "eat"};

int get(int x) { return lower_bound(V.begin(), V.end(), x) - V.begin(); }

int update(int x, int k) {
    x++;
    for (int i = x; i <= N; i += i & (-i))
        t[i] += k;
}

int query(int x) {
    x++;
    int sum = 0;
    for (int i = x; i; i -= i & (-i))
        sum += t[i];
    return sum;
}

int main() {
    scanf("%d %d", &n, &q);
    while (q--) {
        int T, a;
        scanf("%d %d", &T, &a);
        V.emplace_back(a);
        if (T) {
            int b;
            scanf("%d", &b);
            V.emplace_back(b);
            Q.emplace_back(a, b);
        } else
            Q.emplace_back(a, -1);
    }
    sort(V.begin(), V.end());
    V.erase(unique(V.begin(), V.end()), V.end());
    for (pii p : Q) {
        if (p.y == -1)
            cout << S[query(get(p.x)) % 6] << endl;
        else {
            update(get(p.x), 1);
            update(get(p.y) + 1, -1);
        }
    }

    return 0;
}
