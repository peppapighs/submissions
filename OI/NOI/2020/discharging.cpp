#include <bits/stdc++.h>
 
#define long long long
 
using namespace std;
 
const int N = 1e6 + 5;
 
struct CHT {
    struct line {
        long m, c;
        line(long m, long c) : m(m), c(c) {}
        long f(long x) { return m * x + c; }
    };
    vector<line> vec;
 
    bool bad(line a, line b, line c) {
        return 1.0 * (c.c - a.c) / (a.m - c.m) <= 1.0 * (b.c - a.c) /  (a.m - b.m);
    }
 
    void add(long m, long c) {
        line l(m, c);
        while(vec.size() > 1 && bad(vec[(int)vec.size() - 2], vec.back(), l))
            vec.pop_back();
        vec.emplace_back(l);
    }
 
    long get_ans(long x) {
        if(vec.empty()) return 1e18;
        int l = 0, r = (int)vec.size() - 1;
        while(l < r) {
            int mid = (l + r) >> 1;
            if(vec[mid].f(x) >= vec[mid + 1].f(x))
                l = mid + 1;
            else r = mid;
        }
        return vec[r].f(x);
    }
} hull;
 
int n, A[N];
long dp[N];
vector<int> stk;
 
int main() {
    scanf("%d", &n);
    for(int i = n; i; i--) scanf("%d", A + i);
 
    for(int i = 1; i <= n; i++) {
        while(!stk.empty() && A[stk.back()] <= A[i])
            stk.pop_back();
        stk.emplace_back(i);
    }
    for(int i = 0; i < (int)stk.size(); i++) {
        hull.add(A[stk[i]], dp[i - 1]);
        dp[i] = hull.get_ans(stk[i]);
    }
 
    printf("%lld\n", dp[(int)stk.size() - 1]);
 
    return 0;
}