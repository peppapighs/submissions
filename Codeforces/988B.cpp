#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    pair<int, string> s[n];
    for (int i = 0; i < n; i++) {
        cin >> s[i].second;
        s[i].first = s[i].second.length();
    }
    sort(s, s + n);
    bool t = true;
    for (int i = 0; i < n - 1; i++) {
        bool find = false;
        for (int j = 0; j < s[i + 1].second.length() - s[i].second.length() + 1;
             j++) {
            if (s[i + 1].second.substr(j, s[i].second.length()) ==
                s[i].second) {
                find = true;
            }
        }
        if (!find) {
            t = false;
            break;
        }
    }

    if (t) {
        printf("YES\n");
        for (int i = 0; i < n; i++) {
            cout << s[i].second << endl;
        }
    } else {
        printf("NO");
    }

    return 0;
}