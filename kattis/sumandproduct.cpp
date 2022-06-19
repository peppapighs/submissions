#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e5 + 5;

int n;
int A[N], last[N];
vector<int> vec;

int main() {
    scanf("%d", &n);
    last[0] = -1;
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        if (A[i] == 1)
            last[i] = last[i - 1] == -1 ? i : last[i - 1];
        else
            last[i] = -1;
    }

    long ans = 0;
    for (int i = 1; i <= n; i++) {
        int j = i - 1;
        long sum = A[i], prod = A[i];
        while (j > 0) {
            if (A[j] == 1) {
                int add = j - last[j] + 1;
                if (1 <= prod - sum && prod - sum <= add)
                    ++ans;
                sum += add;
                j = last[j] - 1;
            } else {
                sum += A[j];
                if (prod > (long)2e14 / A[j])
                    break;
                prod *= A[j];
                if (sum == prod)
                    ++ans;
                --j;
            }
        }
    }
    printf("%lld\n", ans);

    return 0;
}