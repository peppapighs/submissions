#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e3 + 5;

int n;
int A[N][N], B[N][N];
long l[N], r[N];
mt19937 rnd(time(0));

void mul(int A[N][N], long v[]) {
    long ans[N];
    memset(ans, 0, sizeof ans);
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++)
        ans[i] += A[i][j] * v[j];
    for(int i = 0; i < n; i++) v[i] = ans[i];
}

int main() {
    while(scanf("%d", &n), n != 0) {
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

        bool valid = true;
        for(int _ = 0; _ < 100 && valid; _++) {
            for(int i = 0; i < n; i++)
                l[i] = r[i] = rnd();
            mul(A, l), mul(A, l), mul(B, r);
            for(int i = 0; i < n; i++) if(l[i] != r[i]) {
                valid = false;
                break;
            }
        }
        if(valid) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}