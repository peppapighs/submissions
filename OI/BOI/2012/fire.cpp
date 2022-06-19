#include <bits/stdc++.h>

#define long long long
#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, s;
int x[N], y[N], id[N];
vector<iii> event;

long sum_x[8], sum_y[8], cnt[8];

void add(int i, bool b) {
    if (b)
        sum_x[id[i]] += x[i], sum_y[id[i]] += y[i], ++cnt[id[i]];
    else
        sum_x[id[i]] -= x[i], sum_y[id[i]] -= y[i], --cnt[id[i]];
}

long get_answer(long fx) {
    return sum_y[0] + (sum_x[1] - fx * cnt[1]) +
           (sum_y[2] + (fx + s) * cnt[2] - sum_x[2]) +
           (sum_x[3] - fx * cnt[3] + cnt[3] * s - sum_y[3]) +
           (fx * cnt[4] - sum_x[4]) +
           (fx * cnt[5] - sum_x[5] + cnt[5] * s - sum_y[5]) +
           (sum_y[6] + sum_x[6] - (fx - s) * cnt[6]) + sum_y[7];
}

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", y + i, x + i), y[i] = abs(y[i]);
        sum_x[0] += x[i], sum_y[0] += y[i], ++cnt[0];
        if (y[i] < s) {
            event.emplace_back(x[i] - s, 2, i);
            event.emplace_back(x[i] - y[i], 3, i);
            event.emplace_back(x[i], 5, i);
            event.emplace_back(x[i] + y[i], 6, i);
            event.emplace_back(x[i] + s, 7, i);
        } else {
            event.emplace_back(x[i] - y[i], 1, i);
            event.emplace_back(x[i], 4, i);
            event.emplace_back(x[i] + y[i], 7, i);
        }
    }
    sort(event.begin(), event.end());

    long ans = 1e18;
    for (iii e : event) {
        int fx, type, idx;
        tie(fx, type, idx) = e;
        add(idx, 0);
        id[idx] = type;
        add(idx, 1);
        ans = min(ans, get_answer(fx));
    }
    printf("%lld\n", ans);

    return 0;
}