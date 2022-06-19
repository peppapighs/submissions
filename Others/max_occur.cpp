#include <bits/stdc++.h>

#define pii pair<int, int>

using namespace std;

const int N = 3e4 + 5;
const int M = 3e5 + 5;
const int O = 1e6 + 5;

struct query {
    int l, r, idx;
    query(int l, int r, int idx) : l(l), r(r), idx(idx) {}
    friend bool operator<(const query &a, const query &b) { return a.r < b.r; }
};

int n, q, block, arr[N], freq[O], cl, cr;
vector<vector<query>> bucket;
pii ans[M];
multiset<pii, greater<pii>> wind;

int main() {
    scanf("%d%d", &n, &q);
    block = (int)sqrt(n);
    bucket.resize(block + 5);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    for (int i = 0, a, b; i < q; i++) {
        scanf("%d%d", &a, &b);
        bucket[a / block].emplace_back(a, --b, i);
    }
    for (int i = 0; i < bucket.size(); i++)
        sort(bucket[i].begin(), bucket[i].end());
    for (int i = 0; i < bucket.size(); i++) {
        for (query ask : bucket[i]) {
            int l = ask.l, r = ask.r;
            if (cr > r + 1) {
                int f = l / block;
                f *= block;
                cl = cr = f;
                wind.clear();
                memset(freq, 0, sizeof freq);
            }
            while (cl < l)
                wind.erase({freq[arr[cl]]--, arr[cl]}), cl++;
            while (cl > l)
                cl--, wind.emplace(++freq[arr[cl]], arr[cl]);
            while (cr <= r)
                wind.emplace(++freq[arr[cr]], arr[cr]), cr++;
            ans[ask.idx] = *wind.begin();
        }
    }
    for (int i = 0; i < q; i++)
        printf("%d %d\n", ans[i].second, ans[i].first);

    return 0;
}