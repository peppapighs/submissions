#include <bits/stdc++.h>

using namespace std;

unordered_set<int> arr;

int acc(int n) {
    unordered_set<int>::iterator it = arr.begin();
    advance(it, n);
    return *it;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        arr.insert(x);
    }

    vector<int> st;
    st.push_back(0);

    for (int i = 1; i < n; i++) {
        if (acc(i) >= acc(st[st.size() - 1])) {
            st.push_back(i);
        } else {
            int low = 0, high = st.size() - 1;
            int pos;
            while (high >= low) {
                int mid = (low + high) / 2;
                if (acc(st[mid]) > acc(i)) {
                    high = mid - 1;
                    pos = mid;
                } else {
                    low = mid + 1;
                }
            }
            st[pos] = i;
        }
    }

    printf("%d\n", st.size());
    for (int i = 0; i < st.size(); i++) {
        printf("%d ", st[i]);
    }

    return 0;
}
