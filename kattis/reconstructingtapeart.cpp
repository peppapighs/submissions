#include <bits/stdc++.h>

#define iii tuple<int, int, int>

using namespace std;

const int N = 1e5 + 5;

int n;
int A[N], pref[N], prio[N];
int bl[N], br[N];
vector<iii> ans;

int main() {
    fill_n(bl, N, 1e9);

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        bl[A[i]] = min(bl[A[i]], i);
        br[A[i]] = max(br[A[i]], i);
    }
    for (int i = 1; i <= n; i++)
        if (bl[i] != 1e9) {
            ++pref[bl[i]], --pref[br[i] + 1];
            ans.emplace_back(bl[i], br[i], i);
        }
    for (int i = 1; i <= n; i++) {
        pref[i] += pref[i - 1];
        if (prio[A[i]] != 0 && prio[A[i]] != pref[i])
            return !printf("IMPOSSIBLE\n");
        prio[A[i]] = pref[i];
    }
    sort(ans.begin(), ans.end(),
         [&](iii a, iii b) { return prio[get<2>(a)] < prio[get<2>(b)]; });
    printf("%d\n", (int)ans.size());
    for (iii x : ans) {
        int a, b, c;
        tie(a, b, c) = x;
        printf("%d %d %d\n", a, b, c);
    }

    return 0;
}