# Dynamic Programming

* an optimization problem on DAGs
* Each subproblem is a vertex and there is a directed edge from u to v that is used to calculate v

* Q. Given a target find minimum / maximum, cost / path / sum to reach the target
* A. Choose min / max among all possible paths before current state, then add value for current state

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

{% include '.dp-count.prob' %}

## Digit

* How many numbers x are there in the range a to b, where the digit d occurs exactly k times in x?

{% include '.digit.prob' %}

## Divide concur DP

* Applyes when $$ DP[i] = min_{i\leq j \leq N}F(i, j) $$

{% include '.divide-concur-dp.prob' %}

## Hash DP

{% include '.hash-dp.prob' %}

## Longest Increasing Subsequence

{% include '.longest-increasing-subsequence.prob' %}

## Knapsack

{% include '.knapsack.prob' %}

## Merge

{% include '.merge.prob' %}

## DP Tree

{% include '.dp-tree.prob' %}

## Memoization

{% include '.memoization.prob' %}

## DP String

* Usually done in N ** 2

{% include '.dp-string.prob' %}

### Z Function

![Z-function](images/20210619_194120.png)

* Z algorithm is a linear time string matching algorithm which runs in complexity

{% include '.z-function.prob' %}

### KMP

![KMP](images/20210206_212347.png)

* Knuth-Morris-Pratt searches for occurrences of a "word" W within a main "text string" S
* observe that when a mismatch occurs, the word itself embodies information to determine where the next match begin
* bypass re-examination of previously matched chars

{% include '.kmp.prob' %}

### Suffix Array

{% include '.suffix-array.prob' %}
