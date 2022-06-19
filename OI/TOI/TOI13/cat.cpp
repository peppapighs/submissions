#include <bits/stdc++.h>

using namespace std;

bool check(int s, int line[], int n) {
    int prev = -1;
    for (int i = 0; i < n; i++) {
        if (line[i] > s) {
            if (prev == -1) {
                prev = line[i];
            } else if (prev == line[i]) {
                prev = -1;
            } else {
                return false;
            }
        }
    }

    if (prev != -1) {
        return false;
    }
    return true;
}

int main() {
    int n;
    scanf("%d", &n);
    int line[n];
    int arr[n];

    int prev = -1;
    bool checking = true;

    for (int i = 0; i < n; i++) {
        scanf("%d", &line[i]);
        if (checking) {
            if (prev == -1) {
                prev = line[i];
            } else if (prev == line[i]) {
                prev = -1;
            } else {
                checking = false;
            }
        }

        arr[i] = line[i];
    }

    if (prev == -1) {
        printf("0");
        return 0;
    }

    sort(arr, arr + n);

    int low = 0, high = n - 1;
    int mins;

    while (high >= low) {
        int mid = (high + low) / 2;
        if (check(arr[mid], line, n)) {
            high = mid - 1;
            mins = arr[mid];
        } else {
            low = mid + 1;
        }
    }

    printf("%d", mins);

    return 0;
}
