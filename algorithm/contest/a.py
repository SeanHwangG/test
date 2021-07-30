N, M = map(int, input().split())
s = list(input())
cur = 0
li = [0] * N
for i in range(N):
  if i > 1 and s[i] == s[i - 2]:
    pos = set({'a', 'b', 'c'}) - set(s[i - 2:i + 3])
    try:
      s[i] = pos.pop()
    except:
      try:
        s[i - 2] = (set({'a', 'b', 'c'}) - set(s[i - 2:i + 2])).pop()
      except:
        s[i] = (set({'a', 'b', 'c'}) - set(s[i - 2:i + 2])).pop()
        # s[i - 2] = (set({'a', 'b', 'c'}) - set(s[i - 2:i + 1])).pop()
    cur += 1
  if i > 0 and s[i] == s[i - 1]:
    pos = set({'a', 'b', 'c'}) - set(s[i - 2:i + 3])
    try:
      s[i] = pos.pop()
    except:
      try:
        s[i - 1] = (set({'a', 'b', 'c'}) - set(s[i - 2:i + 2])).pop()
      except:
        s[i] = (set({'a', 'b', 'c'}) - set(s[i - 2:i + 2])).pop()
        # s[i - 1] = (set({'a', 'b', 'c'}) - set(s[i - 2:i + 1])).pop()
    cur += 1
  li[i] = cur
  print(li)
for i in range(M):
  l, r = map(int, input().split())
  print(li[r - 1] - li[l - 1])
