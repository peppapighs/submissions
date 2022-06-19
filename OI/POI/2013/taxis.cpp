#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 5e5 + 5;

long m, d;
int n;
vector<long> vec;

int main() {
    scanf("%lld %lld %d", &m, &d, &n);
    for (int i = 1; i <= n; i++) {
        long a;
        scanf("%lld", &a);
        vec.emplace_back(a);
    }
    sort(vec.begin(), vec.end(), greater<long>());
    int idx = upper_bound(vec.begin(), vec.end(), m - d, greater<long>()) -
              vec.begin() - 1;
    if (idx < 0)
        return !printf("0\n");

    long pos = 0;
    for (int i = 0; i < idx; i++) {
        pos += max(0ll, vec[i] - abs(d - pos));
        if (pos >= m)
            return !printf("%d\n", i + 1);
    }
    if (pos + max(0ll, vec[idx] - abs(d - pos)) >= m)
        return !printf("%d\n", idx + 1);
    for (int i = idx + 1; i < n; i++) {
        pos += max(0ll, vec[i] - abs(d - pos));
        if (pos + max(0ll, vec[idx] - abs(d - pos)) >= m)
            return !printf("%d\n", i + 1);
    }
    printf("0\n");

    return 0;
}