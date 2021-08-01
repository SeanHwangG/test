```py
def kthSmallestPrimeFraction(self, A, K):
  def kthSmallest(matrix, k):
    # Can be improved from LC_378
    return sorted(itertools.chain(*matrix))[k - 1]
  class Row(int):
    def __getitem__(self, j):
      return float(self) / A[~j], [int(self), A[~j]]
  return kthSmallest(map(Row, A), K)[1]
```
