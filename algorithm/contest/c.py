from functools import lru_cache
from itertools import product


def generate(n):
  return [int("".join(r)) for r in product("123", repeat=len(str(n)))]


print(generate(123))


@lru_cache(None)
def solve(n):
  pass


for _ in range(int(input())):
  solve(int(input()))
