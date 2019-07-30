#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 3e5+5;

int n, k, ans;
int A[N];
vector<pii> vec;

int main() {
    scanf("%d %d", &n, &k);
    --k;
    for(int i = 1; i <= n; i++) scanf("%d", A+i);
    for(int i = 1; i < n; i++) vec.emplace_back(A[i+1] - A[i], i);
    sort(vec.begin(), vec.end(), greater<pii>());
    int pv = 1;
    for(int i = 0; i < k; i++) {
        ans += A[vec[i].y] - A[pv];
        pv = vec[i].y + 1;
    }
    ans += A[n] - A[pv];
    printf("%d\n", ans);

    return 0;
}