#include <bits/stdc++.h>

using namespace std;

void update(pair<int, int> *tree, int n, int k, int index) {
    while (index <= n) {
        tree[index].first += k;
        index += index & (-index);
    }
}

int sum(pair<int, int> *tree, int index) {
    int res = 0;
    while (index > 0) {
        res += tree[index].first;
        index -= index & (-index);
    }
    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    pair<int, int> tree[n + 1];

    for (int i = 1; i <= n; i++) {
        tree[i].first = 0;
        scanf("%d", &tree[i].second);
    }

    for (int i = 1; i <= n; i++) {
        update(tree, n, 1, i);
    }

    for (int t = 0; t < n; t++) {
        int ind;
        scanf("%d", &ind);
        int low = 1, high = n;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (sum(tree, mid) <= ind) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        printf("%d\n", tree[low - 1].second);
        update(tree, n, -1, low);
    }

    return 0;
}
