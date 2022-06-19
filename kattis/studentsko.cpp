#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, k;
int A[N];
vector<int> vec;
map<int, int> pos;

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        vec.emplace_back(A[i]);
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < n; i += k)
        for (int j = i; j < i + k; j++)
            pos[vec[j]] = i / k;

    vector<int> lis;
    for (int i = 1; i <= n; i++) {
        if (lis.empty() || lis.back() <= pos[A[i]])
            lis.emplace_back(pos[A[i]]);
        else {
            auto it = upper_bound(lis.begin(), lis.end(), pos[A[i]]);
            if (it != lis.end())
                *it = pos[A[i]];
        }
    }
    printf("%d\n", n - (int)lis.size());

    return 0;
}