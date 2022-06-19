#include "party.h"
#include <bits/stdc++.h>

using namespace std;

int findUnusualGuest(int n, int m, int q) {
    vector<int> A, B;
    for (int i = 0; i < n; i++)
        A.emplace_back(i);
    for (int i = n; i < n + m; i++)
        B.emplace_back(i);

    if (A.size() > B.size())
        swap(A, B);

    vector<int> now = ask(A);
    if (now.size() < B.size())
        for (int x : B)
            if (find(now.begin(), now.end(), x) == now.end())
                return x;

    int l = 0, r = A.size() - 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        vector<int> cur(A.begin() + l, A.begin() + mid + 1);
        if (ask(cur).size() > cur.size())
            r = mid;
        else
            l = mid + 1;
    }

    return A[r];
}
