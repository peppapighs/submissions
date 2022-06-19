#include <bits/stdc++.h>

using namespace std;

map<int, int> rep;

bool compare(const pair<int, int> &a, const pair<int, int> &b) {
    return a.first > b.first;
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    vector<pair<int, int>> sk;
    int arr[n];
    for (int i = 0; i < n; i++) {
        pair<int, int> x;
        scanf("%d", &x.first);
        arr[i] = x.first;
        x.second = i;
        sk.push_back(x);
        rep[x.first]++;
    }
    sort(sk.begin(), sk.end(), compare);
    int m[n];
    for (int i = 0; i < n; i++) {
        m[sk[i].second] = n - i - rep[sk[i].first];
        rep[sk[i].first]--;
    }
    for (int i = 0; i < k; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (arr[--a] > arr[--b]) {
            m[a]--;
        }
        if (arr[a] < arr[b]) {
            m[b]--;
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", m[i]);
    }

    return 0;
}
