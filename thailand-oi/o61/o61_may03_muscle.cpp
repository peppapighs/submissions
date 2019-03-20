#include <bits/stdc++.h>

using namespace std;

const int N = 5e5+5;

int n, t[N];
int A[N], ans[N];

void update(int x, int k) { for(int i = x; i < N; i += i & -i) t[i] += k; }
int query(int x, int ret = 0) { for(int i = x; i; i -= i & -i) ret += t[i]; return ret; }

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", A+i), update(i, 1);
    for(int i = n; i; i--) {
        int l = 1, r = n;
        while(l < r) {
            int mid = (l + r) >> 1;
            if(query(mid) >= i - A[i]) r = mid;
            else l = mid + 1;
        }
        ans[i] = r;
        update(r, -1);
    }
    for(int i = 1; i <= n; i++) printf("%d ", ans[i]);
    printf("\n");

    return 0;
}
