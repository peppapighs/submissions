#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define x first
#define y second

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

//-----------------------------------------------------------

int t;

int main() {
    scanf("%d", &t);
    while (t--) {
        string s;
        cin >> s;
        bool l = false, u = false, n = false;
        int a = -1, b = -1, c = -1;
        for (int i = 0; i < s.length(); i++) {
            if ('a' <= s[i] && s[i] <= 'z')
                l = true, a = i;
            if ('A' <= s[i] && s[i] <= 'Z')
                u = true, b = i;
            if ('0' <= s[i] && s[i] <= '9')
                n = true, c = i;
        }
        if (!l)
            for (int i = 0; i < s.length(); i++)
                if (i != b && i != c) {
                    s[i] = 'a';
                    a = i;
                    break;
                }
        if (!u)
            for (int i = 0; i < s.length(); i++)
                if (i != a && i != c) {
                    s[i] = 'A';
                    b = i;
                    break;
                }
        if (!n)
            for (int i = 0; i < s.length(); i++)
                if (i != a && i != b) {
                    s[i] = '0';
                    c = i;
                    break;
                }
        cout << s << endl;
    }

    return 0;
}
