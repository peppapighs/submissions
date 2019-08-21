#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, A[N];
map<int, int> m1, m2;
vector<pii> v1, v2;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", A + i);
    for(int i = 1; i <= n; i++) {
        if(i & 1) ++m1[A[i]];
        else ++m2[A[i]];
    }
    for(auto p : m1) v1.emplace_back(p);
    for(auto p : m2) v2.emplace_back(p);
    sort(v1.begin(), v1.end(), [&](const pii &a, const pii &b) {
        return a.y > b.y;
    });
    sort(v2.begin(), v2.end(), [&](const pii &a, const pii &b) {
        return a.y > b.y;
    });
    if(m1.size() == 1 && m2.size() == 1 && m1.begin()->x == m2.begin()->x) printf("%d\n", n / 2);
    else if(v1[0].x == v2[0].x) printf("%d\n", n - v1[0].y - max(v1[1].y, v2[1].y));
    else printf("%d\n", n - v1[0].y - v2[0].y);

    return 0;
}