N = int(input())
A, a = [*sorted(map(int, input().split()))], 0
B, b = [*sorted(map(int, input().split()))], 0
C, c = [*sorted(map(int, input().split()))], 0

ret = 0
while max(a, b, c) < N:
  print('a', a, A[a])
  print('b', b, B[b])
  print('c', c, C[c])
  if A[a] < B[b] < C[c]:
    a, b, c = a + 1, b + 1, c + 1
    ret += 1
  elif A[a] >= B[b]:
    b = b + 1
  elif B[b] >= C[c]:
    c = c + 1
print(ret)
