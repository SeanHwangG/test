# Divide Concur

> multiply Algorithm

$$ x = 2^{n/2}x_L + x_R $$
$$ y = 2^{n/2}y_L + y_R $$

{% tabs %}
{% tab title='multiply.py' %}

```py
# O(N)
def multiply (x: int, y: int) -> int:
  If n = 1 : return xy
  xL, xR and yL, yR are left-most and right-most n/2 bits of x and y, respectively.
  P1 = multiply(xL, yL)
  P2 = multiply(xL, yR)
  P3 = multiply(xR, yL)
  P4 = multiply(xR, yR)
  return P1 * 2**n + (P2 + P3) * 2 ** (n / 2) + P4
```

{% endtab %}
{% endtabs %}

## Master theorem

* Calculates Complexity for divide and conquer algorithm
  $$
  T(n)=a T\left(\frac{n}{b}\right)+O\left(n^{d}\right)
  $$

  $$
  T(n) \epsilon\left\{\begin{array}{ll}
  O\left(n^{d}\right) & \text { top heavy: } a<b^d \\
  O\left(n^{d} \log n\right) & \text { steady : } a=b^{d} \\
  O\left(n^{\log _{b} a}\right) & \text { bottom heavy: } a>b^{d}
  \end{array}\right.
  $$

* Cook Toom: multiplication algorithm for large integers
  * Run Time $$ Θ(n^{1.46}) $$

> Example

* Master Theorem Proof
  * After k levels, there are $$a^k$$ subproblems, each of size $$\frac{n}{b^k}$$
  * So, during the kth level of recursion, the time complexity
  $$
  O\left(\left(\frac{n}{b^{k}}\right)^{d}\right) a^{k}=O\left(a^{k}\left(\frac{n}{b^{k}}\right)^{d}\right)=O\left(n^{d}\left(\frac{a}{b^{d}}\right)^{k}\right)
  $$

## Binary Search

* while (start <= end): if are returning the match from inside the loop
* while (start < end): if want to exit out of the loop first, and then use result of start or end to return the match

{% tabs %}
{% tab title='cpp' %}

* ForwardIt lower_bound(): return It pointing to first in range which does not compare less than val

```cpp
#include <algorithm>
#include <vector>

// 1. Binary Search in sorted array
vector<int> v{ 10, 20, 30, 40, 50 };
lower_bound(v.begin(), v.end(), 10); // 0
```

{% endtab %}
{% tab title='python' %}

* bisect
  * bisect_left(`nums`, `x`): first insert point for x in `nums` to maintain sorted order
  * bisect_right(`nums`, `x`): last insert point for x in `nums` to maintain sorted order
    * lo=0, hi=len(a): set where to start, end in array
  * insort_left(`a`, `x`, lo=**0**, hi=**len(a)**): insert `x` in `a` in sorted order
    * a.insert(bisect_left(a, x, lo, hi), x): a must be sorted
    * O(log n) search is dominated by the slow O(n) insertion step
  * insort(`a`, `x`, lo=0, hi=len(a)): inserting `x` in `a` after any existing entries of x, O(N) due to insert

* requests
  * json(): convert back to

* cgi: dynamically generating web pages that respond to user input

```py
# 1. Search on sorted list
def index(a, x):
  'Locate the leftmost value exactly equal to x'
  i = bisect_left(a, x)
  if i != len(a) and a[i] == x: return i
  raise ValueError

def find_lt(a, x):
  'Find rightmost value less than x'
  i = bisect_left(a, x)
  if i: return a[i-1]
  raise ValueError

def find_le(a, x):
  'Find rightmost value less than or equal to x'
  i = bisect_right(a, x)
  if i: return a[i-1]
  raise ValueError

def find_gt(a, x):
  'Find leftmost value greater than x'
  i = bisect_right(a, x)
  if i != len(a): return a[i]
  raise ValueError

def find_ge(a, x):
  'Find leftmost item greater than or equal to x'
  i = bisect_left(a, x)
  if i != len(a): return a[i]
  raise ValueError
```

{% endtab %}
{% endtabs %}

{% include '.binary-search.prob' %}

### Parametric Search

{% include '.parametric-search.prob' %}

### Ternary Search

{% include '.ternary-search.prob' %}

## Quick Select

{% tabs %}
{% tab title='cpp' %}

* void nth_element( RandomIt first, RandomIt nth, RandomIt last )
  * All elements before this new nth element are less or equal to elements after the new nth element

{% endtab %}
{% tab title='sql' %}

```sql
-- 1. SQL cannot express all computable queries ⇒ Is there a way to get from CITY1 to city2
---- Way from city1 to city2 with at most 2 stop over.
SELECT x.from z.to FROM flight x, flight y, flight z
WHERE x.from = 'city1' AND x.to = y.from AND y.to = z.from AND z.to = 'city2'

-- 2. Way from city1 to city with at most k stopovers.
---- Intuition : (SELECT * FROM T_{k-1}) UNION (SELECT x.A, y.B FROM G x, T_{k - 1} y WHERE x.B = y.A)
WITH RECURSIVE T AS (SELECT * FROM G) UNION
(SELECT x.A, y.B FROM G x, T y WHERE x.B = y.A) SELECT * FROM T;

-- 3. Find transitive closure of friend (drinkers who frequent the same bar) / frequent = (frequents, drinker, bar)
CREATE RECURSIVE VIEW T AS
  (SELECT f1.drinker AS drinker1, f2.drinker AS drinker2 FROM frequent f1, frequent f2
WHERE f1.bar = f2.bar) UNION
  (SELECT t1.drinker1, f2.drinker AS drinker2 FROM T t1, frequents f1, frequents f2
WHERE t1.drinker2 = f1.drinker AND f1.bar = f2.bar)
```

{% endtab %}
{% endtabs %}

{% include '.quick-select.prob' %}

### Quick Select 2d

> Example

* Sorting
  * Time: O(n^2 * log(n^2))
  * Space: O(n^2)
* PriorityQueue
  * Time: O(n^2 * logk)
  * Space: O(k)
* Binary Search
  * Time: O(n * log(MAX - MIN))
  * Space: O(1)

{% tabs %}
{% tab title='cpp' %}

* void cv::minMaxIdx(): find the minimum and maximum element values and their positions
  * InputArray src
  * double* minVal
  * double* maxVal = 0
  * int* minIdx = 0
  * int* maxIdx = 0
  * InputArray mask = noArray()

{% endtab %}
{% endtabs %}

{% include '.quick-select-2d.prob' %}

> Reference

<https://leetcode.com/problems/k-th-smallest-prime-fraction/discuss/115819/Summary-of-solutions-for-problems-%22reducible%22-to-LeetCode-378>

## Meet in the middle

{% include '.meet-in-the-middle.prob' %}

## Recursion

[Recursion](https://www.youtube.com/watch?v=kx6DfrYfWnQ)

[Finbonacci](https://www.youtube.com/watch?v=zg-ddPbzcKM)

{% include '.recursion.prob' %}

### Backtrack

* Bounding function: kill some live nodes without actually expanding them
* generic method that can be applied to problems with large solution set, in search and optimization problems
* often be a first step towards finding a greedy or dynamic programming algorithm
* often gives a more efficient runtime over exhaustive search or brute force
* but may not result in a polynomial time algorithm, and is usually an improved exponential time (also for NP-complete problems)
* Often, they are better on typical inputs that their worst-cast
* Difference between divide and conquer is decrease size by a factor vs difference
* Problem analysis
  * Instance: What does the input look like?
  * Solution format: What does the output look like?
  * Constraints: What properties must a solution have?
  * Objective function: What makes a solution have?

> Example

* 8 Queen: Put 8 queens on a chessboard such that no two are attacking
  * Brute force: Put all possible arrangements of 8 queens on the chess board
    * Instance: An empty 8 x 8 chess board
    * Solution format: A placement of 8 queens
    * Constraint: No two queens are attacking
    * Object: Find a solution with the constraint
  * Consider one row at a time, eliminating possible non-solution board positions early in their construction

{% include '.backtrack.prob' %}
