#include "traffic.h"
#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define iiii tuple<int, int, int, int>

using namespace std;

int n, k;
int a1, a2, a3, a4;
int b1, b2, b3, b4;
vector<iii> V;
vector<iiii> ans;

int main() {
    traffic_init(&n, &k);
    for (int i = 1; i <= n; i++) {
        int now = traffic_query(i, 1, i, n);
        if (now > n - 1)
            V.emplace_back(i, 0, now);
    }
    for (int i = 1; i <= n; i++) {
        int now = traffic_query(1, i, n, i);
        if (now > n - 1)
            V.emplace_back(0, i, now);
    }
    for (iii q : V) {
        int a, b, k;
        tie(a, b, k) = q;
        if (a) {
            int l = 1, r = n - 1;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (traffic_query(a, 1, a, mid + 1) >= mid + k - n + 1)
                    r = mid;
                else
                    l = mid + 1;
            }
            ans.emplace_back(a, r, a, r + 1);
            if (traffic_query(a, 1, a, n) == n)
                continue;
            l = 1;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (traffic_query(a, 1, a, mid + 1) > mid)
                    r = mid;
                else
                    l = mid + 1;
            }
            ans.emplace_back(a, r, a, r + 1);
        } else {
            int l = 1, r = n - 1;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (traffic_query(1, b, mid + 1, b) >= mid + k - n + 1)
                    r = mid;
                else
                    l = mid + 1;
            }
            ans.emplace_back(r, b, r + 1, b);
            if (traffic_query(1, b, n, b) == n)
                continue;
            l = 1;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (traffic_query(1, b, mid + 1, b) > mid)
                    r = mid;
                else
                    l = mid + 1;
            }
            ans.emplace_back(r, b, r + 1, b);
        }
    }
    tie(a1, a2, a3, a4) = ans[0];
    if (k == 1)
        traffic_report(a1, a2, a3, a4, 0, 0, 0, 0);
    else {
        tie(b1, b2, b3, b4) = ans[1];
        traffic_report(a1, a2, a3, a4, b1, b2, b3, b4);
    }

    return 0;
}
