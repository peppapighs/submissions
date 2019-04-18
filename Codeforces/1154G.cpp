#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e7+5;

int n, A[N], pos[N], sieve[N];
pii ans[N];

int main() {
    fill_n(ans, N, pii(1e9, 1e9));
    iota(pos, pos+N, 0);
    scanf("%d", &n);
    for(int i = 2; i < N; i++) {
        if(sieve[i]) continue;
        for(int j = i; j < N; j += i)
            sieve[j] = i;
    }
    for(int i = 1; i <= n; i++) scanf("%d", A+i);
    sort(pos+1, pos+n+1, [&](const int &a, const int &b) {
        return A[a] < A[b];
    });
    for(int i = 1, a; i <= n; i++) {
        a = A[pos[i]];
        if(i > 2 && A[pos[i-2]] == a) continue;
        vector<pii> v;
        while(a != 1) {
            int d = sieve[a];
            if(!v.empty() && v.back().x == d) ++v.back().y;
            else v.emplace_back(d, 1);
            a /= d; 
        }
        function<void(int, int)> gen_div = [&](int idx, int now) {
            if(idx == (int)v.size()) {
                if(ans[now].x == 1e9) ans[now].x = pos[i];
                else if(ans[now].y == 1e9) ans[now].y = pos[i];
                if(ans[now].x > ans[now].y) swap(ans[now].x, ans[now].y);
                return;
            }
            for(int j = 0, dpow = 1; j <= v[idx].y; j++) {
                gen_div(idx + 1, now * dpow);
                dpow *= v[idx].x;
            }
        };
        gen_div(0, 1);
    }
    long lcm = 1e18;
    int a = -1, b = -1;
    for(int i = 1; i < N; i++) {
        if(ans[i].x == 1e9 || ans[i].y == 1e9) continue;
        long curl = 1ll * A[ans[i].x] * A[ans[i].y] / i;
        if(curl < lcm) lcm = curl, a = ans[i].x, b = ans[i].y;
    }
    printf("%d %d\n", a, b);

    return 0;
}