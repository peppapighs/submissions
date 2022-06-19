#include <bits/stdc++.h>
#include <set>
#include <string>

using namespace std;

set<string> x;

int main() {
    int n;
    scanf("%d", &n);

    while (n--) {
        string s;
        string b = "";
        cin >> s;
        bool ch[26] = {false};
        for (int i = 0; i < s.length(); i++) {
            ch[s[i] - 'a'] = true;
        }
        for (int i = 0; i < 26; i++) {
            if (ch[i]) {
                b = b + (char)('a' + i);
            }
        }
        sort(b.begin(), b.end());
        x.insert(b);
    }

    printf("%d", x.size());

    return 0;
}
