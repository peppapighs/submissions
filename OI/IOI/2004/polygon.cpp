#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e3 + 5;

int n;
vector<pii> vert, E, P;

bool cross(pii v1, pii v2) {
    return (1ll * v1.x * v2.y - 1ll * v2.x * v1.y) < 0;
}

pii get_prim(pii p) {
    int g = abs(__gcd(p.x, p.y));
    return pii(p.x / g, p.y / g);
}

pii get_min(vector<pii> &vec) {
    int mnx = 1e9, mny = 1e9;
    for (pii p : vec)
        mnx = min(mnx, p.x), mny = min(mny, p.y);
    return pii(mnx, mny);
}

vector<pii> subtract(vector<pii> &P, vector<pii> &A) {
    vector<pii> B;
    for (pii p1 : P) {
        pii vec1 = get_prim(p1);
        bool valid = false;
        for (pii p2 : A) {
            pii vec2 = get_prim(p2);
            if (vec1 == vec2) {
                valid = true;
                if (p1 != p2)
                    B.emplace_back(p1.x - p2.x, p1.y - p2.y);
                break;
            }
        }
        if (!valid)
            B.emplace_back(p1);
    }
    return B;
}

vector<pii> get_coord(vector<pii> &vec) {
    vector<pii> ret = {pii(0, 0)};
    for (pii p : vec)
        ret.emplace_back(ret.back().x + p.x, ret.back().y + p.y);
    ret.pop_back();

    pii mn = get_min(ret);
    for (pii &p : ret)
        p.x -= mn.x, p.y -= mn.y;
    return ret;
}

void shift(vector<pii> &A, vector<pii> &B, vector<pii> &P) {
    pii a = get_min(A), b = get_min(B), p = get_min(P);
    for (pii &now : B) {
        now.x += p.x - a.x - b.x;
        now.y += p.y - a.y - b.y;
    }
}

void answer(vector<pii> &A) {
    printf("%d\n", (int)A.size());
    for (pii p : A)
        printf("%d %d\n", p.x, p.y);
}

int main() {
    scanf("%d", &n);

    vert.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &vert[i].x, &vert[i].y);
    for (int i = 0; i < n; i++) {
        int x = vert[(i + 1) % n].x - vert[i].x,
            y = vert[(i + 1) % n].y - vert[i].y;
        int g = abs(__gcd(x, y));

        for (int j = 1; j <= g; j++)
            E.emplace_back(x / g * j, y / g * j);
        P.emplace_back(x, y);
    }
    sort(E.begin(), E.end());

    vector<pii> A;

    function<bool()> solve_vec = [&]() {
        for (pii vec : E) {
            pii inv(-vec.x, -vec.y);
            auto it = lower_bound(E.begin(), E.end(), inv);
            if (it == E.end() || *it != inv)
                continue;

            A.emplace_back(vec), A.emplace_back(*it);
            break;
        }

        vector<pii> B = subtract(P, A);
        vector<pii> poly_A = get_coord(A), poly_B = get_coord(B);
        shift(poly_A, poly_B, vert);

        if ((int)poly_A.size() == 2) {
            answer(poly_A), answer(poly_B);
            return true;
        }
        return false;
    };

    function<bool()> solve_tri = [&]() {
        for (int i = 0; i < (int)E.size(); i++) {
            bool valid = false;
            for (int j = i + 1; j < (int)E.size(); j++) {
                pii now(E[i].x + E[j].x, E[i].y + E[j].y);
                auto it = lower_bound(E.begin(), E.end(), pii(-now.x, -now.y));
                if (it == E.end() || *it != pii(-now.x, -now.y))
                    continue;

                A.emplace_back(E[i]), A.emplace_back(E[j]), A.emplace_back(*it);
                valid = true;
                break;
            }
            if (valid)
                break;
        }
        vector<pii> B = subtract(P, A);
        vector<pii> poly_A = get_coord(A), poly_B = get_coord(B);
        shift(poly_A, poly_B, vert);

        if ((int)poly_A.size() == 3) {
            answer(poly_A), answer(poly_B);
            return true;
        }
        return false;
    };

    // Answer might be the input itself (wrong!)
    function<bool()> solve_qua = [&]() {
        vector<pii> tmp;
        for (int i = 0; i < (int)E.size(); i++)
            for (int j = i + 1; j < (int)E.size(); j++)
                tmp.emplace_back(E[i].x + E[j].x, E[i].y + E[j].y);

        sort(tmp.begin(), tmp.end());
        for (int i = 0; i < (int)E.size(); i++) {
            bool valid = false;
            for (int j = i + 1; j < (int)E.size(); j++) {
                if (get_prim(E[i]) == get_prim(E[j]))
                    continue;
                pii now(E[i].x + E[j].x, E[i].y + E[j].y);
                if (now.x == 0 && now.y == 0)
                    continue;

                auto it =
                    lower_bound(tmp.begin(), tmp.end(), pii(-now.x, -now.y));
                if (it == tmp.end() || *it != pii(-now.x, -now.y))
                    continue;

                A.emplace_back(E[i]), A.emplace_back(E[j]);
                for (int k = 0; k < (int)E.size(); k++)
                    if (k != i && k != j) {
                        bool found = false;
                        for (int l = k + 1; l < (int)E.size(); l++)
                            if (l != i && l != j && E[k].x + E[l].x == -now.x &&
                                E[k].y + E[l].y == -now.y) {
                                if (get_prim(E[k]) == get_prim(E[l]))
                                    continue;
                                if (cross(A[0], A[1]) != cross(E[k], E[l]))
                                    A.emplace_back(E[l]), A.emplace_back(E[k]);
                                else
                                    A.emplace_back(E[k]), A.emplace_back(E[l]);
                                found = true;
                                break;
                            }
                        if (found)
                            break;
                    }
                valid = true;
                break;
            }
            if (valid)
                break;
        }
        vector<pii> B = subtract(P, A);
        vector<pii> poly_A = get_coord(A), poly_B = get_coord(B);
        shift(poly_A, poly_B, vert);

        if ((int)poly_A.size() == 4 && (int)poly_B.size() >= 2) {
            answer(poly_A), answer(poly_B);
            return true;
        }
        return false;
    };

    if (solve_qua())
        return 0;
    A.clear();
    if (solve_tri())
        return 0;
    A.clear();
    solve_vec();

    return 0;
}