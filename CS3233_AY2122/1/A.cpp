#include <bits/stdc++.h>

using namespace std;

vector<string> finger = {"thumb",         "index finger", "middle finger",
                         "ring finger",   "pinky",        "ring finger",
                         "middle finger", "index finger"};

char str[100];

int main() {
    while (scanf(" %s", str) != EOF) {
        int now = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            now = (now * 10 + (str[i] - '0')) % 8;
        }
        cout << finger[(now + 7) % 8] << "\n";
    }

    return 0;
}