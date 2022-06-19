#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

int HC(int n) {
    Guess(1);
    int l = 1, r = n;
    int last = 0, pre = 1;
    while (l < r) {
        if (r - l < 3) {
            if (last == 0) {
                int now = Guess(r);
                if (now == 0)
                    return l + 1;
                else if (now == 1)
                    return r;
                else
                    return l;
            } else {
                int now = Guess(l);
                if (now == 0)
                    return l + 1;
                else if (now == 1)
                    return l;
                else
                    return r;
            }
        } else {
            if (last == 0) {
                int now = Guess(r);
                if (now == 0)
                    return (pre + r) / 2;
                else if (now == 1) {
                    l = (l + r) / 2 + 1;
                    pre = r, last = 1;
                } else {
                    r = (l + r + 1) / 2 - 1;
                    Guess(pre);
                }
            } else {
                int now = Guess(l);
                if (now == 0)
                    return (pre + l) / 2;
                else if (now == 1) {
                    r = (l + r + 1) / 2 - 1;
                    pre = l, last = 0;
                } else {
                    l = (l + r) / 2 + 1;
                    Guess(pre);
                }
            }
        }
    }
    return l;
}
