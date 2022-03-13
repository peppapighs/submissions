#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n;
mt19937 rng(time(0));
long X[N], Y[N];

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%lld %lld", X + i, Y + i);
    for(int _ = 0; _ < 100; _++) {
        int a = rng() % n, b = rng() % (n - 1);
        if(b >= a) ++b;

        vector<int> vec;
        for(int i = 0; i < n; i++) if(i != a && i != b)
            if((Y[a] - Y[b]) * (X[a] - X[i]) != (Y[a] - Y[i]) * (X[a] - X[b]))
                vec.emplace_back(i);
        if((int)vec.size() <= 2) return !printf("success\n");

        bool ok = true;
        int l = vec[0], r = vec[1];
        for(int ptr = 2; ptr < (int)vec.size(); ptr++) {
            int i = vec[ptr];
            ok &= ((Y[l] - Y[r]) * (X[l] - X[i]) == (Y[l] - Y[i]) * (X[l] - X[r]));
        }
        if(ok) return !printf("success\n");
    }
    printf("failure\n");

    return 0;
}