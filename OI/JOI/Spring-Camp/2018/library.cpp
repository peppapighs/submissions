#include "library.h"
#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e3 + 5;
const int M = 98765431;

long mpow[N];
map<long, int> mp;

int ask(vector<int> &v) {
    if (!accumulate(v.begin(), v.end(), 0))
        return 0;

    long hsh = 0;
    for (int i = 0; i < v.size(); i++)
        if (v[i])
            hsh += mpow[i];
    if (!mp.count(hsh))
        return mp[hsh] = Query(v);
    else
        return mp[hsh];
}

int n;
vector<int> vec, ans;

void Solve(int _n) {
    mpow[0] = 1, n = _n;
    for (int i = 1; i < N; i++)
        mpow[i] = mpow[i - 1] * M;
    vec = vector<int>(n);

    int l = 0, r = n - 1;
    while (l < r) {
        int mid = (l + r) >> 1;

        vector<int> now = vec;
        for (int i = l; i <= mid; i++)
            now[i] = 1;

        int q1 = ask(now);
        for (int i = 0; i < n; i++)
            now[i] ^= 1;
        int q2 = ask(now);

        if (q1 >= q2)
            r = mid;
        else
            l = mid + 1;
    }
    ans.emplace_back(r + 1), vec[r] = 1;
    for (int i = 1; i < n; i++) {
        int l = 0, r = n - 1;
        while (l < r) {
            int mid = (l + r) >> 1;

            vector<int> now = vec;
            for (int i = l; i <= mid; i++)
                now[i] = 1;

            int q1 = ask(now);
            now[ans.back() - 1] = 0;
            int q2 = ask(now);

            if (i == 1) {
                if (q1 == q2)
                    r = mid;
                else
                    l = mid + 1;
            } else {
                if (q1 < q2)
                    r = mid;
                else
                    l = mid + 1;
            }
        }
        ans.emplace_back(r + 1), vec[r] = 1;
    }

    Answer(ans);
}
