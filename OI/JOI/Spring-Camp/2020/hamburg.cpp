#include <bits/stdc++.h>

using namespace std;

struct Rectangle {
    int x1, y1, x2, y2;
    Rectangle() : x1(1), y1(1), x2(1e9), y2(1e9) {}
    Rectangle(int x1, int y1, int x2, int y2)
        : x1(x1), y1(y1), x2(x2), y2(y2) {}
    friend Rectangle operator+(const Rectangle &a, Rectangle &b) {
        Rectangle ret;
        ret.x1 = max(a.x1, b.x1), ret.y1 = max(a.y1, b.y1);
        ret.x2 = min(a.x2, b.x2), ret.y2 = min(a.y2, b.y2);
        return ret;
    }
};

const int N = 2e5 + 5;

int n, k;
vector<Rectangle> rect;
bitset<N> chk;
default_random_engine rng(time(NULL));

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1, x1, y1, x2, y2; i <= n; i++) {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        rect.emplace_back(x1, y1, x2, y2);
    }
    while (true) {
        chk.reset();
        vector<Rectangle> vec(k);
        for (int i = 0; i < k; i++)
            for (int j = 0; j < n; j++) {
                if (chk[j])
                    continue;
                Rectangle now = vec[i] + rect[j];
                if (now.x1 <= now.x2 && now.y1 <= now.y2)
                    chk[j] = 1, vec[i] = now;
            }
        if (chk.count() == n) {
            for (int i = 0; i < k; i++)
                printf("%d %d\n", vec[i].x1, vec[i].y1);
            return 0;
        }
        vector<Rectangle> nex;
        for (int i = 0; i < n; i++)
            if (!chk[i])
                nex.emplace_back(rect[i]);
        shuffle(nex.begin(), nex.end(), rng);
        for (int i = 0; i < n; i++)
            if (chk[i])
                nex.emplace_back(rect[i]);
        swap(rect, nex);
    }

    return 0;
}