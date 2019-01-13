#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n;
pii A[N], B[N];
pii dp1[N], dp2[N];

int main() {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) scanf("%d %d", &A[i].x, &A[i].y);
        for(int i = 1; i <= n; i++) scanf("%d %d", &B[i].x, &B[i].y);
        sort(B+1, B+n+1);
        dp1[1] = B[1];
        for(int i = 2; i <= n; i++) {
                if(B[i].x - dp1[i-1].x + B[i].y - dp1[i-1].y > 0) dp1[i] = B[i];
                else dp1[i] = dp1[i-1];
        }
        dp2[n] = B[n];
        for(int i = n-1; i; i--) {
                if(dp2[i+1].x - B[i].x + B[i].y - dp2[i+1].y > 0) dp2[i] = B[i];
                else dp2[i] = dp2[i+1];
        }
        for(int i = 1; i <= n; i++) {
                int l = 1, r = n, ans = INT_MIN;
                while(l < r) {
                        int m = (l + r + 1) >> 1;
                        if(A[i].x >= dp1[m].x) l = m;
                        else r = m-1;
                }
                ans = max(ans, A[i].y + dp1[l].y - abs(dp1[l].x - A[i].x));
                l = 1, r = n;
                while(l < r) {
                        int m = (l + r) >> 1;
                        if(A[i].x <= dp2[m].x) r = m;
                        else l = m+1;
                }
                ans = max(ans, A[i].y + dp2[r].y - abs(A[i].x - dp2[r].x));
                printf("%d\n", ans);
        }

        return 0;
}
