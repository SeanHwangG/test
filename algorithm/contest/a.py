import heapq

n, m = int(input()), int(input())
G = [[] for _ in range(n + 1)]
parent = [None] * (n + 1)
for _ in range(m):
  a, b, c = map(int, input().split())
  G[a].append((c, b))

start, end = map(int, input().split())
dist = [10**10 + 1] * (n + 1)
dist[start] = 0
pq = [(0, start)]
while pq:
  d, i = heapq.heappop(pq)
  if dist[i] != d:
    continue
  if i == end:
    break
  for e, j in G[i]:
    if e + d < dist[j]:
      dist[j] = e + d
      parent[j] = i
      heapq.heappush(pq, (dist[j], j))

path = [end]
while path[-1] != start:
  path.append(parent[path[-1]])
print(dist[end])
print(len(path))
print(*reversed(path))
