#include <bits/stdc++.h>

using namespace std;

string t, p;

bool lcs(int k, int *arr) {
    string tmp = t;
    for (int i = 0; i <= k; i++) {
        tmp[arr[i] - 1] = ' ';
    }
    int i = 0, j = 0;
    while (i < tmp.size() && j < p.size()) {
        if (p[j] == tmp[i]) {
            j++;
        }
        i++;
    }
    return j == p.size();
}

int main() {
    cin >> t >> p;
    int arr[t.size()];

    for (int i = 0; i < t.size(); i++) {
        scanf("%d", &arr[i]);
    }

    int low = 0, high = t.size() - 1;
    int res = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (lcs(mid, arr)) {
            low = mid + 1;
            res = mid;
        } else {
            high = mid - 1;
        }
    }

    printf("%d", res + 1);

    return 0;
}
