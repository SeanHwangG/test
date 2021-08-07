from collections import defaultdict

N, M = map(int, input().split())
alive, dead = set(), set(range(1, N + 1))
d = defaultdict(lambda: (0, 0))  # Smaller, Bigger
conn = defaultdict(set)


def connect(a, b):
  global alive, dead
  conn[a].add(b)
  conn[b].add(a)
  if a < b:
    a, b = b, a
  print('c', a, b)
  d[a] = (d[a][0] + 1, d[a][1])
  d[b] = (d[b][0], d[b][1] + 1)

  if d[a][0] == 1:
    alive.add(a)
    dead.remove(a)


def disconnect(a, b):
  global alive, dead
  conn[a].remove(b)
  conn[b].remove(a)
  if a < b:
    a, b = b, a
  print('d', a, b)
  d[a] = (d[a][0] - 1, d[a][1])
  d[b] = (d[b][0], d[b][1] - 1)
  if d[a][0] == 0:
    alive.add(a)
    dead.remove(b)


for _ in range(M):
  connect(*map(int, input().split()))
  print(alive, dead, d)

for _ in range(int(input())):
  try:
    t, a, b = map(int, input().split())
    if t == 1:
      connect(a, b)
    elif t == 2:
      disconnect(a, b)
  except:
    print(len(alive))
