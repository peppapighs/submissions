#include <bits/stdc++.h>

using namespace std;

const int N = 105;

int n, a, b, ans[N];

int main() {
    scanf("%d %d %d", &n, &a, &b);
    if(a + b > n + 1) return !printf("IMPOSSIBLE\n");
    if(a + b == n + 1) {
        for(int i = b; i; i--) ans[b - i + 1] = i;
        for(int i = b + 1; i <= n; i++) ans[i] = i;
    } else {
        bool chk = a > b;
        if(a > b) swap(a, b);
        vector<int> v(b, 1);
        int sum = b, tmp = 0;
        for(int i = 0; i < b; i++) {
            int x = a - 1;
            if(sum + x <= n) sum += x, v[i] += x;
            else {
                v[i] += n - sum;
                sum = n;
            }
        }
        if(sum != n) return !printf("IMPOSSIBLE\n");
        for(int i = 0; i < b; i++) {
            int x = tmp, y = tmp + v[i];
            for(int j = y; j > x; j--) ans[++tmp] = j;
        }
        if(!chk) reverse(ans + 1, ans + n + 1);
    }
    for(int i = 1; i <= n; i++) printf("%d ", ans[i]);
    printf("\n");

    return 0;
}