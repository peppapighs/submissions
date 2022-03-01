#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e6 + 5;

int n;

int main() {
    scanf("%d", &n);

    vector<long> ans;
    vector<long> vec;
    for(int i = 1; i <= n; i++) {
        long a;
        scanf("%lld", &a);
        vector<long> tmp;
        for(long &x : vec)
            tmp.emplace_back(__gcd(x, a));
        tmp.emplace_back(a);

        sort(tmp.begin(), tmp.end());
        tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());

        for(long &x : tmp) ans.emplace_back(x);
        vec = tmp;
    }
    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
    
    printf("%d\n", (int)ans.size());

    return 0;
}