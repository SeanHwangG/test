from collections import deque

n, m, k = map(int, input().split())
D = [[*input()] for _ in range(n)]
G = [[[0] * (k + 1) for _ in range(m)] for _ in range(n)]
G[0][0][0] = 1
q = deque([[0, 0, 0]])
while q:
  x, y, z = q.popleft()
  for nx, ny in [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]:
    if 0 <= nx < n and 0 <= ny < m:
      if D[nx][ny] == '0' and G[nx][ny][z] == 0:
        q.append([nx, ny, z])
        G[nx][ny][z] = G[x][y][z] + 1
      if D[nx][ny] == '1' and z < k and G[nx][ny][z + 1] == 0:
        q.append([nx, ny, z + 1])
        G[nx][ny][z + 1] = G[x][y][z] + 1
ans = float('inf')
for x in G[n - 1][m - 1]:
  if x != 0:
    ans = min(ans, x)
print([ans, -1][ans == float('inf')])
