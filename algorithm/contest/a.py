from collections import defaultdict


def ret(li):
    N = len(li)
    i2j = defaultdict(int)
    for i in range(N):
        for j in range(i - 1):
            n, m = li[i], li[j]
            i2j[i] = min(i2j[abs(m - n) + j - i], j)
    print(i2j)


for _ in range(int(input())):
    input()
    print(ret(list(map(int, input().split()))))
