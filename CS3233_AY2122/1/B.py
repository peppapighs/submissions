from fractions import Fraction

T = int(input())

for step in range(0, T):
        x1, n1, x2, n2 = input().split()
        ans = Fraction(int(x1), 10 ** len(x1)) + Fraction(int(x2), 10 ** len(x2))
        if int(n1) != 0:
                rep = int(x1) % (10 ** int(n1)) 
                ans += Fraction(rep, 10 ** (len(x1)) * (10 ** int(n1) - 1))
        if int(n2) != 0:
                rep = int(x2) % (10 ** int(n2))
                ans += Fraction(rep, 10 ** (len(x2)) * (10 ** int(n2) - 1))
        print(str(ans.numerator) + '/' + str(ans.denominator))