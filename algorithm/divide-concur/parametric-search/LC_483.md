```py
def smallestGoodBase(self, n: str) -> str:
  def is_valid(base, size):
    """returns 0 if total == n, pos if n > total and neg if n < total"""
    total = sum(base ** i for i in range(size))
    return n - total
  n = int(n)
  N = len(bin(n)[2:])
  for size in range(N, 0, -1):
    lo, hi = 2, n - 1
    while lo <= hi:
      mi = (lo + hi) // 2
      v = is_valid(mi, size)
      if v < 0:
        hi = mi - 1
      elif v > 0:
        lo = mi + 1
      else:
        return str(mi)
```
