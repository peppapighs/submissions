def get_comb(x):
    if x == " ":
        return "0"
    if x == "z":
        return "9999"
    if x == "s":
        return "7777"
    now = ord(x)
    if now > ord("s"):
        now -= 1
    return str(2 + (now - ord('a')) // 3) * ((now - ord('a')) % 3 + 1)

T = int(input())

for _ in range(0, T):
    s = input()
    ans = ""
    for x in s:
        now = get_comb(x)
        if len(ans) > 0 and ans[-1] == now[0]:
            ans += " "
        ans += now
    print(f"Case #{_ + 1}: {ans}")
