#include <bits/stdc++.h>

#define long long long

using namespace std;

int n;
long ret;
vector<long> V, ans;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        long a;
        cin >> a;
        V.emplace_back(a);
    }
    for (int i = 63; ~i; i--) {
        long ret = 0;
        for (long x : V)
            if ((x >> i) & 1)
                ret = x;
        if (ret == 0)
            continue;
        ans.emplace_back(ret);
        for (long &x : V)
            if ((x >> i) & 1)
                x ^= ret;
    }
    for (long x : ans)
        if ((ret ^ x) > ret)
            ret ^= x;
    cout << ret << endl;

    return 0;
}
