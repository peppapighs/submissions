#include <bits/stdc++.h>

using namespace std;

bool can = true;
map<char, bool> vowel;

int main() {
    vowel['a'] = true;
    vowel['e'] = true;
    vowel['i'] = true;
    vowel['o'] = true;
    vowel['u'] = true;
    string s;
    cin >> s;

    char prev = s[0];
    for (int i = 1; i < s.length(); i++) {
        if (prev != 'n' && !vowel[prev] && !vowel[s[i]]) {
            can = false;
            break;
        }
        prev = s[i];
    }
    if (!vowel[s[s.length() - 1]] && s[s.length() - 1] != 'n')
        can = false;

    if (can)
        printf("YES");
    else
        printf("NO");

    return 0;
}