# Dynamic Programming

* an optimization problem on DAGs
* Each subproblem is a vertex and there is a directed edge from u to v that is used to calculate v

* Q. Given a target find minimum / maximum, cost / path / sum to reach the target
* A. Choose min / max among all possible paths before current state, then add value for current state

> Reference

<https://www.educative.io/courses/grokking-dynamic-programming-patterns-for-coding-interviews>

## DP Dimension 0

{% include '.dp-dimension-0.prob' %}

## DP Dimension 1

{% include '.dp-dimension-1.prob' %}

## DP Dimension 2

{% include '.dp-dimension-2.prob' %}

### DP Dimension 2 Area

{% include '.dp-dimension-2-area.prob' %}

### DP Dimension 2 Path

* Choose min(max) path among all possible paths before the current state, then add value for the current state
  * routes[i] = min(routes[i-1], routes[i-2], ... , routes[i-k]) + cost[i]

{% include '.dp-dimension-2-path.prob' %}

### Tabulation

{% include '.tabulation.prob' %}

## DP Bit

{% include '.dp-bit.prob' %}

## DP Count

* Sum all possible ways to reach the current state
  * routes[i] = routes[i-1] + routes[i-2], ... , + routes[i-k]

> Example

{% include '.dp-count.prob' %}

## Digit DP

* How many numbers x are there in the range a to b, where the digit d occurs exactly k times in x?

> Example

{% include '.digit-dp.prob' %}

## Divide concur DP

* Applyes when $$ DP[i] = min_{i\leq j \leq N}F(i, j) $$

> Example

{% include '.divide-concur-dp.prob' %}

## Hash DP

{% include '.hash-dp.prob' %}

## Longest Increasing Subsequence

{% include '.longest-increasing-subsequence.prob' %}

## Knapsack

* Given the weights and profits of ‘N’ items, put items in a knapsack that has a capacity ‘C’
* Goal is to get the maximum profit from the items in the knapsack
* [ex] subset sum, target sum

![Knapsack](images/20210726_224742.png)

> Term

* **01 knapsack**: Repetition item is not allowed

> Example

* N=number of items, C=knapsack capacity
* DP: dp[idx][cap] = max(dp[idx - 1][cap], profit[idx] + dp[idx][cap - weight[idx]])
  * Time: O(N*C)
  * O(C) for optimized DP

* Memoization
  * Space: O(N*C)

{% include '.knapsack.prob' %}

### Unbounded Knapsack

* Repetetition item is allowed
* [ex] coin change, rod cutting

{% include '.unbounded-knapsack.prob' %}

## DP Merge

{% include '.dp-merge.prob' %}

## DP Tree

{% include '.dp-tree.prob' %}

## Memoization

{% include '.memoization.prob' %}

## DP String

* Usually done in N ** 2

{% include '.dp-string.prob' %}

### Manacher

![Manacher](images/20210808_025822.png)

* O(N) Time Longest Palindromic Substring

{% include '.manacher.prob' %}

### Z Function

![Z-function](images/20210619_194120.png)

* Z algorithm is a linear time string matching algorithm which runs in complexity

{% include '.z-function.prob' %}

### KMP

![KMP](images/20210206_212347.png)

* Knuth-Morris-Pratt searches for occurrences of `word` within `text` without re-examination of previously matched chars
* Observe that when a mismatch occurs, the word itself embodies information to determine where the next match begin
* O(n) in worst case
* [+] Easier to implement
* [ex] DNA pattern matching problem

> Term

* Failure function: aka partial match table
  ![Failure function](images/20210806_232230.png)
  * pi[i]: length of longest possible proper initial segment of W which is also segment of substring ending at W[i - 1]

> Example

{% include '.kmp.prob' %}

> Reference

<https://www.youtube.com/watch?v=V5-7GzOfADQ>

### Suffix Array

![Suffix Array](images/20210801_165935.png)

* Time
  * O(n^2 Logn): Build Suffix Array
  * O(mlogn):
* Space O(m+n): Suffix Array
* [+] Find substring repetitions
* [ex] Pattern Searching, longest repeated substring, longest common substring, longest palindrome in a string

> Example

{% include '.suffix-array.prob' %}
