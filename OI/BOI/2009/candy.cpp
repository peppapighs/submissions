#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n;
vector<int> wagon;
vector<iii> ans;
pii A[N];

int main() {
    scanf("%d", &n);
    for(int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        A[i] = pii(b - a, b + a);
    }
    sort(A + 1, A + n + 1);
    for(int i = 1; i <= n; i++) {
        int id;
        auto it = lower_bound(wagon.begin(), wagon.end(), A[i].y, greater<int>());
        if(it != wagon.end()) *it = A[i].y, id = it - wagon.begin() + 1;
        else wagon.emplace_back(A[i].y), id = wagon.size();
        ans.emplace_back((A[i].y - A[i].x) / 2, (A[i].x + A[i].y) / 2, id);
    }
    printf("%d\n", (int)wagon.size());
    for(iii t : ans) {
        int a, b, c; tie(a, b, c) = t;
        printf("%d %d %d\n", a, b, c);
    }

    return 0;
}