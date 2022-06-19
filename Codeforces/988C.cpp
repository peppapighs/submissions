#include <bits/stdc++.h>

using namespace std;

map<int, int> p;
map<int, int> pos;

int main() {
    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        int n, sum = 0;
        scanf("%d", &n);
        int arr[n];
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[j]);
            sum += arr[j];
        }
        for (int j = 0; j < n; j++) {
            arr[j] = sum - arr[j];
            if (p[arr[j]] != 0 && p[arr[j]] != i + 1) {
                printf("YES\n");
                printf("%d %d\n", i + 1, j + 1);
                printf("%d %d", p[arr[j]], pos[arr[j]]);
                return 0;
            } else {
                p[arr[j]] = i + 1;
                pos[arr[j]] = j + 1;
            }
        }
    }

    printf("NO");

    return 0;
}