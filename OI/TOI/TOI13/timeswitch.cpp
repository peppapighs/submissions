#include "bits/stdc++.h"

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    string s;
    cin >> s;
    int kmp[n];
    kmp[0] = 0;
    for (int i = 1; i < n; i++) {
        int j = kmp[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = kmp[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        kmp[i] = j;
    }
    int len = n - kmp[n - 1];
    if (n % len == 0) {
        printf("%d", len);
    } else {
        printf("%d", n);
    }

    return 0;
}
