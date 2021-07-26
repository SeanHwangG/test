import sys

input = sys.stdin.readline


def main(players):
  def win(a, b):
    return sum([g1 < g2 for g1, g2 in zip(players[a], players[b])]) >= 3

  lost = set()
  for i in range(len(players)):
    if i in lost:
      continue
    for j in range(len(players)):
      if i != j and not win(i, j):
        break
      lost.add(j)
    else:
      return i + 1
  return -1


for _ in range(int(input())):
  print(main([list(map(int, input().split())) for _ in range(int(input()))]))
