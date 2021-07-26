def main(li):
  li = [n]
  N = len(li)
  if 0 in li or len(li) != len(set(li)):
    return True
  se = set(li)
  for _ in range(N - 2):
    newse = se.copy()
    for s in se:
      for i in range(N):
        d = li[i] - s
        if d in li:
          return True
        newse.add(d)
    se = newse
  return False


# print(main([0]), True)
# print(main([1]), False)
# print(main([1, 2]), False)
# print(main([1, 2, 3]), True)
print(main([1, 2, 4]), False)

for _ in range(int(input())):
  input()
  li = list(map(int, input().split()))
  # print("YES" if main(li) else "NO")
"""
  def dfs(i):
    if i == N:
      return all(n is None for n in li)

    for j in range(i):
      for k in range(N):
        if li[k] is None:
          continue
        ret[i] = ret[j] - li[k]
        temp = li[k]
        li[k] = None
        dfs(i + 1)
        li[k] = temp
    return False
"""
