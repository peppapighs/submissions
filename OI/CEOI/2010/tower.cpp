#include <bits/stdc++.h>
 
#define long long long
 
using namespace std;
 
const int N = 1e6 + 5;
const int M = 1e9 + 9;
 
int n, d, A[N];
long ans = 1;
 
int main() {
    scanf("%d %d", &n, &d);
    for(int i = 1; i <= n; i++) scanf("%d", A + i);
 
    sort(A + 1, A + n + 1);
    for(int i = 1, j = 0; i <= n; i++) {
        while(j + 1 < i && A[j + 1] + d < A[i])
            ++j;
        ans = ans * (i - j) % M;
    }
    printf("%lld\n", ans);
 
    return 0;
}