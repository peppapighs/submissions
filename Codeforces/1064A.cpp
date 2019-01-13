#include <bits/stdc++.h>

using namespace std;

int a, b, c;
int cnt;

void sort(int &a, int &b, int &c) {
        if(a > b) swap(a, b);
        if(a > c) swap(a, c);
        if(b > c) swap(b, c);
}

int main() {
        scanf("%d %d %d", &a, &b, &c);
        sort(a, b, c);
        printf("%d\n", max(0, c - b - a + 1));

        return 0;
}
