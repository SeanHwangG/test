# Reinforcement Learning

> Terms

* Tasks

```sh
Episodic Tasks    # Interaction breaks into episodes, which end with a terminal state.
Continuing Tasks  # Interaction goes on continually without terminal state.
```

* Policy
  * Target: One we are learning
  * Behavior: One we are choosing action from

* Generalized policy iteration (GPI)
  * interaction between policy-evaluation and policy improvement

* Planning
  * any process that takes input model, and improves a policy

* Backup Diagram

| Notation  | Term                                                                         |
| --------- | ---------------------------------------------------------------------------- |
| K         | Number of actions                                                            |
| t         | Discrete time step                                                           |
| qk(a)     | Expected value of action a                                                   |
| Qt(a)     | Estimate at time t of q*(a)                                                  |
| πt(a)     | Probability of selecting action a at time t                                  |
| ρt        | importance sampling ratio for time t                                         |
| δt        | TD Error at time t Rt+1 γV(St+1) - V(St)                                     |
| d         | dimensionality—the number of components of w                                 |
| v̂(s, w)   | approximate value of state s given weight vector w (Σwixi(s), or neural net) |
| b(a \| s) | Behavior policy used to select actions while learning about target policy π  |

![Backup Diagram](images/20210301_193635.png)

## RL Model

![Models](images/20210222_225900.png)

* Actor critic

```text
Input:
  Differentiable policy parameterization π(a | s, θ)
  Differentiable state-value function parameterization v̂(s, w)
Initialize:
  R̄ ∈ R to 0
  State-value weights w ∈ Rd and policy parameter θ ∈ Rd (e.g. to 0)
  Algorithm parameters: αw > 0, αθ > 0, αR̄ > 0
  S ∈ S
Loop:
  A ~ π( · | S, θ)
  Take action A, observe S’, R
  δ ← R - R̄ + v̂(S’, w) - v̂(S, w)
  R̄ ← R̄ + αR̄δ
  w ← w + αw δ ∇ v̂(S, w)
  θ ← θ + αθ δ ∇ln π(A | S, θ)
  S ← S’
```

* Dyna

```text
# Q+
Initialize:
  Q(s, a) and Model(s, a) for all s 2 S and a 2 A(s)
Loop forever:
  S ← current (nonterminal) state
  A ← e-greedy(S, Q)
  Take action A: observe resultant reward, R, and state, S'
  Q(S, A) ← Q(S, A) + α [R + γ maxaQ(S', a) - Q(S, A)]
  Model(S, A) ← R, S'
  Loop repeat n times:
    S ← random previously observed state
    A ← random action previously taken in S
    R, S' ← Model(S, A)
    Q(S, A) ← Q(S, A) + α[(R + κτ0.5) + R + γ maxaQ(S', a) - Q(S, A)]
```

* Monte Carlo

```text
# e-soft
Input : a policy π to be evaluated, ε > 0
Initialize:
  π ← an arbitrary ε-soft policy
  Q(s, a) ∈ R (arbitrarily) for all s ∈ S, a ∈ A(s)
  Returns(s, a) ← an empty list, for all s ∈ S, a ∈ A(s).
Loop:
  Generate an episode from S0, A0, following π : S0, A0, R1, …, ST-1, AT-1, RT
  G ← 0
  Loop for each step of episode, t = T - 1, T - 2, ..., 0:
    G ← γG + Rt+1
    Append G to Returns(St, At)
    Q(St, At) ← average(Returns(St, At))
    A* ← argmaxa Q(St, a)
    For all a ∈ A(St):


# Exploring start
Initialize:
  π(s) ∈ A(s)  (arbitrarily), for all s ∈ S.
  Q(s, a) ∈ R (arbitrarily), for all s ∈ S, a ∈ A(s).
  Returns(s, a) ← an empty list, for all s ∈ S, a ∈ A(s).
Loop:
  Choose S0 ∈ S, A0 ∈ A(S0) randomly s.t. all pairs have probability > 0
  Generate an episode from S0, A0, following π : S0, A0, R1, …, ST-1, AT-1, RT
    G ← return that follows the first occurence of s, a
    Append G to Returns(s, a)
    Q(s, a) ← average(Returns(s, a))
    For each s in the episode:
      π(s) ← argmaxa Q(s, a)

# Off-policy
Input:
  an arbitrary target policy π
Initialize, for all s ∈ S, a ∈ A(s):
  Q(s, a) ← arbitrary
  C(s, a) ← 0
Repeat:
  b ← any policy with coverage of π
  Generate an episode using b:
  S0, A0, R1, …, ST - 1, AT - 1, RT, ST
  G ← 0
  W ← 1
  For t = T - 1, T - 2, … down to 0:
    G ← γG + Rt+1
    C(St, At) ← C(St, At) + W
    Q(St, At) ← Q(St, At) + W | C(St, At) [G - Q(St, At)]
    W ← W π(At|St) | b(At|St)
    If W = 0 then exit For loop

# Prediction
Initialize:
  π ← policy to be evaluated
  V ← an arbitrary state-value function
  Returns(s) ← an empty list, for all s ∈ S
Repeat forever:
  Generate an episode using π
  For each state s appearing in the episode:
    G ← the return that follows the first occurrence of s
    Append G to Returns(s)
    V (s) ← average(Returns(s))
```

* Value Iteration

![Value Iteration](images/20210301_193519.png)

* Policy Iteration

![Policy Iteration](images/20210301_193452.png)

* SARSA

```text
# Differential Semi-G
Initialize state S, and action A
Loop for each step:
  Take action A, observe R, S’
  Choose A’ as a function of q̂(S’, ·, w) (e.g. ε-greedy)
  δ ← R - R̄+ q̂(S’, A’, w) - q̂(S, A, w)
  R̄ ← R̄ + β δ
  w ← w + αδ ∇q̂(S, A, w)
  S ← S’
  A ← A’

# Expected
Loop for each episode:
  Initialize S
  Choose A from S using policy derived from Q (e.g. ε-greedy)
  Loop for each step of episode:
    Take action A, observe R, S’
    Choose A’ from S’ using policy derived Q (e.g. ε-greedy)
    Q(S, A) ← Q(S, A) + α[R + γQ(S’, A’) - Q(S, A)]
    Q(S, A) ← Q(S, A) + α[R + γΣaπ(a | St+1)Q(St+1, a) - Q(St, At)]
    S ← S’; A ← A’;
  until S is terminal
```

* Q Learning

```text
Initialize:
  Q(s, a) = random, for all s ∈ S, a ∈ A(s)
  Q(terminal, *) = 0
Loop:
  Initialize S
  Loop for each step of episode:
    Choose A from S using policy derived from Q (e.g. e-greedy)
    Take action A, observe R, S'
    Q(S, A) ← Q(S, A) + α [R + γ maxa Q(S', a) - Q(S, A)]
    S ← S'
  until S is terminal
```

* Q planning

```text
Loop:
  Select a state, S ∈ S, and an action, a ∈ A(s) at random
  Send s, a to a sample model, and obtain a sample next reward, R, and a sample next state, S'
  Apply one-step tabular Q-learning to S, A, R, S'
    Q(S, A) ← Q(S, A) + α[ R + γmaxaQ(S', a) - Q(S, A)]
```

* TD0

```text
Input:
  policy π to be evaluated, step size α
Initialize:
  V(s), for all s ∈ S+, arbitrarily except that V(terminal) = 0
Loop for each episode:
  Initialize S
  Loop for each step of episode:
    A ← action given by π for S
    Take action A, observer R, S'
    V(S) ← V(S) + α[R + γV(s') - V(S)]
    S ← S'
  until S is terminal

# Semi-Gradient
Loop for each episode:
  Initialize S
  Loop for each step of episode:
    Choose A ~ π(*|S)
    Take action A, observe R, S'
    w ← w + α[R + γ v̂(S', w) - v̂(S, w)] Δv̂(S, w)
    S ← S'
until S is terminal
```
