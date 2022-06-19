#include "combo.h"
#include <bits/stdc++.h>

using namespace std;

string ret;
vector<string> f = {"A", "B", "X", "Y"};

string guess_sequence(int N) {
    if (press("AB")) {
        if (press("A"))
            ret = "A";
        else
            ret = "B";
    } else {
        if (press("X"))
            ret = "X";
        else
            ret = "Y";
    }
    for (int i = 0; i < 4; i++)
        if (f[i] == ret)
            f.erase(f.begin() + i);
    for (int i = 1; i < N - 1; i++) {
        string t = ret + f[0] + f[0] + ret + f[0] + f[1] + ret + f[0] + f[2] +
                   ret + f[1];
        int r = press(t);
        if (r == i + 2)
            ret += f[0];
        else if (r == i + 1)
            ret += f[1];
        else
            ret += f[2];
    }
    if (N > 1) {
        if (press(ret + f[0]) == N)
            ret += f[0];
        else if (press(ret + f[1]) == N)
            ret += f[1];
        else
            ret += f[2];
    }
    return ret;
}
