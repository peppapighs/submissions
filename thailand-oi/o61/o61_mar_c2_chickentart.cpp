#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5+5;

int n, m, k;
int A[N], l[N], r[N];

bool f(int mid) {
    memset(l, 0, sizeof l), memset(r, 0, sizeof r);
    long sum = A[1], cnt = 1;
    l[1] = A[1] > mid ? 1e9 : 1;
    for(int i = 2; i <= n; i++) {
        if(l[i-1] == 1e9 || A[i] > mid) {
            l[i] = 1e9;
            continue;
        }
        l[i] = l[i-1];
        if(sum + A[i] <= mid && cnt + 1 <= m) sum += A[i], ++cnt;
        else ++l[i], sum = A[i], cnt = 1;
    }
    sum = A[n], cnt = 1;
    r[n] = A[n] > mid ? 1e9 : 1;
    for(int i = n-1; i; i--) {
        if(r[i+1] == 1e9 || A[i] > mid) {
            r[i] = 1e9;
            continue;
        }
        r[i] = r[i+1];
        if(sum + A[i] <= mid && cnt + 1 <= m) sum += A[i], ++cnt;
        else ++r[i], sum = A[i], cnt = 1;
    }
    for(int i = 1, j = m; j <= n; i++, j++) if(l[i-1] + r[j+1] + 1 <= k) return true;
    return false;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 1; i <= n; i++) scanf("%d", A+i);
    int l = 0, r = 1e9;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(f(mid)) r = mid;
        else l = mid+1;
    }
    printf("%d\n", r);

    return 0;
}
