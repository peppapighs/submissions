#include <bits/stdc++.h>

using namespace std;

void print(const char *c, int x) {
    printf(c, x);
    fflush(stdout);
}

int x, y;

int main() {
    while(scanf("%d %d", &x, &y), x != -1 && y != -1) {
        if(x < y) {
            if(y - x <= y / 2)  print("H %d\n", y - x);
            else {
                int now = x;
                while(2 * now + 1 < y) now = 2 * now + 1;
                print("H %d\n", y - now);
            }
        } else {
            if(x - y <= x / 2) print("V %d\n", x - y);
            else {
                int now = y;
                while(2 * now + 1 < x) now = 2 * now + 1;
                print("V %d\n", x - now);
            }
        }
    }

    return 0;
}