#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int res = 0;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (arr[u - 1] < arr[v - 1]) {
            res += arr[u - 1];
        } else {
            res += arr[v - 1];
        }
    }

    printf("%d", res);

    return 0;
}
