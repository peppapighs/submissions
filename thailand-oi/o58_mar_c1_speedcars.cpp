#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5+5;

int n, ans;
long T, t[N], A[N];
vector<long> V;

int get(int x) { return lower_bound(V.begin(), V.end(), x) - V.begin(); }

void update(int x, int k) { for(int i = x+1; i; i -= i & -i) t[i] += k; }

long query(int x) {
    long ret = 0;
    for(int i = x+1; i < N; i += i & -i) ret += t[i];
    return ret;
}

int main() {
    scanf("%d %lld", &n, &T);
    for(int i = 1; i <= n; i++) {
        long a, b;
        scanf("%lld %lld", &b, &a);
        A[i] = a * T + b;
        V.emplace_back(a * T + b);
    }
    sort(V.begin(), V.end());
    V.erase(unique(V.begin(), V.end()), V.end());
    for(int i = 1; i <= n; i++) {
        if(!query(get(A[i]))) ++ans;
        update(get(A[i]), 1);
    }
    printf("%d\n", ans);

    return 0;
}