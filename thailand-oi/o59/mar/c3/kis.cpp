#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 105;

int n, l;
long k;
int A[N], pos[N];
long t[N][N];

void update(long t[], int x, long v) { for(int i = x+1; i > 0; i -= i & -i) t[i-1] += v; }

long query(long t[], int x) {
    long ret = 0;
    for(int i = x+1; i <= n; i += i & -i) ret += t[i-1];
    return ret;
}

long get(long t[], int x) { return query(t, x) - query(t, x+1); }

int main() {
    scanf("%d %d %lld", &n, &l, &k);
    for(int i = 1; i <= n; i++) scanf("%d", A+i), pos[A[i]] = i;
    for(int i = n; i; i--) for(int j = 0; j <= l; j++)
        update(t[j], A[i], (j == 0) + query(t[j], A[i]) + (j ? query(t[j-1], 0) - query(t[j-1], A[i]) : 0));
    int ptr = 0, skip = 0;
    vector<int> ans;
    for(int it = 0; it < n; it++) {
        bool have = true;
        for(int i = 0; i < n; i++) {
            if(pos[i] <= ptr || k < 0) continue;
            long sum = 0;
            for(int j = 0; j <= l - skip - (i < A[ptr]); j++) sum += get(t[j], i);
            if(k - sum < 0) {
                ans.emplace_back(i);
                if(i < A[ptr]) ++skip;
                ptr = pos[i], --k;
                have = false;
                break;
            } else k -= sum;
        }
        if(have) break;
    }
    if(ans.empty()) return !printf("-1\n");
    for(int a : ans) printf("%d ", a);
    printf("\n");

    return 0;
}