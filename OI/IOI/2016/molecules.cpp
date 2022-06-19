#include "molecules.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

vector<pii> V;
vector<int> ans;

vector<int> find_subset(int l, int u, vector<int> w) {
    for (int i = 0; i < w.size(); i++)
        V.emplace_back(w[i], i);
    sort(V.begin(), V.end());
    int L = 0, R = 0;
    long long sum = 0;
    while (L < w.size()) {
        while (R < w.size() && sum < l)
            sum += (long long)V[R++].x;
        if (l <= sum && sum <= u) {
            for (int i = L; i < R; i++)
                ans.emplace_back(V[i].y);
            return ans;
        }
        sum -= (long long)V[L++].x;
    }
    return {};
}
