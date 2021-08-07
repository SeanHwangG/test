for _ in range(int(input())):
  n = int(input())
  A, B = list(map(int, input())) + [0], list(map(int, input()))
  #    00    01    10     11
  d = {0: 0, 1: -1, 2: -1, 3: -1}
  for i in range(n):
    a, b = A[i], B[i]
    if b == 0:
      d[0], d[1], d[2], d[3] = max(d[0], d[2]), -1, max(d[2], d[3]), -1
    else:
      d[0], d[1], d[2], d[3] = max(d[0], d[2]) + A[i - 1], max(d[0], d[2]) if A[i + 1] else -1, max(d[3], d[1] + A[i - 1], max(d[0], d[2]) + (a ^ 1)), max(d[1], d[3]) + A[i + 1] if A[i + 1] else -1
    print(a, b, d)

  print(max(d[0], d[2]))
