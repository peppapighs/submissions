#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e3 + 5;

int n, h, A[N];

int main() {
    scanf("%d %d", &n, &h);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i);
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        vector<int> V;
        for (int i = 1; i <= mid; i++)
            V.emplace_back(A[i]);
        sort(V.begin(), V.end(), greater<int>());
        long sum = 0;
        for (int i = 0; i < mid; i += 2)
            sum += V[i];
        if (sum <= h)
            l = mid;
        else
            r = mid - 1;
    }
    printf("%d\n", l);

    return 0;
}
