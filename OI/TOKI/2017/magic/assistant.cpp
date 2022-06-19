#include "assistant.h"
#include <bits/stdc++.h>

#define long long long

using namespace std;

static long hsh(vector<int> &v) {
    long iden = 6969, ret = 0;
    for (int i = 0; i < v.size(); i++)
        ret = ret * iden + v[i];
    return ret;
}

static int n, k;
static vector<int> v;
static map<long, int> M1, M2;

static void gen_permute(int u) {
    if (v.size() == k) {
        for (int i = 1; i <= n; i++)
            if (find(v.begin(), v.end(), i) == v.end()) {
                vector<int> now = v;
                now.emplace_back(i);
                sort(now.begin(), now.end());
                long h = hsh(now);
                if (!M1.count(h)) {
                    M1[h] = i, M2[hsh(v)] = i;
                    return;
                }
            }
    } else
        for (int i = u + 1; i <= n; i++) {
            v.emplace_back(i);
            gen_permute(i);
            v.pop_back();
        }
}

void initAssistant(int _n, int _k) {
    n = _n, k = _k;
    gen_permute(0);
}

int giveClue(vector<int> cards) { return M2[hsh(cards)]; }