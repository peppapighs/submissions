from fractions import Fraction

T = int(input())

for _ in range(0, T):
    a, b, c = input().split()
    K, M = [int(a), int(b)]
    if not "." in c:
        print(str(K) + " 0/1")
    else:
        x = Fraction(int(c.split(".")[1]), 10 ** len(c.split(".")[1]))
        l = Fraction(0, 1)
        r = Fraction(1, 1)
        ans = Fraction(0, 1)
        for i in range(0, 5000):
            mid = Fraction(l.numerator + r.numerator, l.denominator + r.denominator)
            if mid.denominator > M:
                break

            if mid <= x:
                l = mid
                if (ans <= x and x - ans > x - mid) or (ans > x and ans - x > x - mid):
                    ans = mid
            else:
                r = mid
                if (ans <= x and x - ans > mid - x) or (ans > x and ans - x > mid - x):
                    ans = mid
        print(str(K) + " " + str(ans.numerator) + "/" + str(ans.denominator))