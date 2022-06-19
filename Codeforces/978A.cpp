#include <bits/stdc++.h>

using namespace std;

int main() {
    bool k[1001] = {false};
    int n;
    scanf("%d", &n);
    int arr[n];
    vector<int> z;
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        if (!k[arr[i]]) {
            z.push_back(arr[i]);
            k[arr[i]] = true;
        }
    }
    printf("%d\n", z.size());
    for (int i = z.size() - 1; i >= 0; i--) {
        printf("%d ", z[i]);
    }

    return 0;
}
