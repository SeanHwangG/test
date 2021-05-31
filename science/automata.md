# Automata

* the study of abstract computing devices, or machines
* Turing studied an abstract machine (Turing machine) that had all the capabilities of today’s computers
  * goal was to describe precisely the boundary between what a computing machine could do and what it could not do

![Automata](images/20210407_200833.png)

> Terms

* language: a set of words consists of words over some alphabet
  * can take set operations: unions, intersections, complementation
  * universal set is the set of all possible words over $$ \Sigma $$
* Finite language: if there exists a number k ∈ N ,st for every string w ∈ L, |w| ≤ k
  * For any given k , we have that every L ∈ P (Σk) is a finite language

$$ L(M) = \{w : w \text{ is word over }\Sigma, w \text{ is accepted by m} \} $$

* string: finite sequence of characters
* word: specific set of characters in $$ \Sigma $$
  * concatnation: $$ w o v $$

## Regular Language

* Language that can be expressed with a regular expression
* a deterministic or non-deterministic finite automata or state machine
* A Regular expression R over an alphabet $$ \Sigma $$ is either

| Base case                     | Recursive case                                 |
| ----------------------------- | ---------------------------------------------- |
| $$ \empty $$                  | $$ R_1 \cup R_2 $$ where $$ R_1, R_2 $$ are RE |
| $$ \{ϵ\} $$                   | $$ R_1 \cdot R_2 $$                            |
| $$ \{a\} $$, $$a \in \Sigma$$ | $$ R_1^* $$                                    |

* Closure properties: regular languages are closed under union, intersection, complement, dot, kleene star opertions

> Operation

| Term                  | Symbol      | Property                                                                       |
| --------------------- | ----------- | ------------------------------------------------------------------------------ |
| complementation       | $$ ^c $$    | universel set $$ \beta $$ exists                                               |
| kleene star operation | $$ R^{*} $$ | $$ \{ w_1 \cdot w_2 \cdot ... \cdot w_n: w_i \in R \text{ and } n \geq 0 \} $$ |
| concatenation         | $$ \cdot $$ | $$ R_1 \cdot R_2 = \{ w \cdot v : w \in R_1 \cup v \in R_2 \} $$               |
| intersections         | $$ \cap $$  | binary                                                                         |
| union                 | $$ \cup $$  | binary                                                                         |

> Proof Regular language is closed under complementation

* Let R be a regular language, and let $$ M = (Q, \Sigma, \sigma, q_0, F) $$ be a DFA for $$ R $$
* Then define $$ N = (Q, \Sigma, \sigma, q_0, Q \ F, F^c) $$
* Claim
  * $$ L(N) = R^c $$
  * $$ L(N) \subseteq R^c, R^c \subseteq L(N) $$

> Proof Regular Language is closed under intersection

* Let R1, R2 be regular languages, with DFAs
* $$ M1 = (Q_1, \Sigma, \sigma, q_{0, 1}, F, F_1), M2 = (Q, \Sigma, \sigma_2, q_{0, 2}, F_2) $$ respectively
* Define $$ M = (Q_1 \times Q_2, \Sigma, \sigma_1 \times \sigma_2, (q_{0, 1}, q_{0, 2}), F_1 \times F_2) $$
  * $$ \sigma((q_i, q_j), a) = (\sigma_1(q_i, a), \sigma_2(q_j, a)) $$

> Proof Regular Language is closed under union

* $$ (F_1 \times Q_2) \cup (Q_1 \times F_2) $$
* Alternatively we can note $$ R_1 \cup R_2 = [(R_1 \cup R_2)^c]^c = (R^{c}_{1} \cap R^{c}_{2})^c $$

> Proof Regular Language is closed under Kleene star operation

* If R is a language, then

$$ R* = {w_1 \cdot w_2 \cdot ... \cdot w_n: w_i \in R, n \leq 0 } $$

* note taking n = 0 gives $$ ϵ $$
* With regular language R with NFA $$ M = (Q, Σ, σ, q_0, F) $$, wwt define a NFA $$ N = (\text{s.t. } L(N)=R^*) $$

* $$ M = (Q, \Sigma, \sigma, q_0, F) $$, $$ L(M) = R $$
* $$ N = (Q, \sqcup, {\hat{q}_0}, \Sigma, \hat{\sigma}, \hat{q_0}, F \sqcup \{\hat{q_0}\}) $$
* $$ \hat{\sigma}(\hat{q_0}, ϵ) = \{q_0\} $$
* $$ \hat{\sigma}(\hat{q_0}, a) = \empty $$, if $$ a \in \Sigma $$
* $$ \hat{\sigma}(\sigma, ϵ) = \{ q_0 \} \cup \sigma(q, ϵ) $$, else if $$ q \in F $$
* $$ \hat{\sigma}(q, a) = \sigma(q, a) $$, else

* Claim $$ L(N) = R^* $$

> Proof Every Regular Expression is describing a RL

* Base case: Show that $$ \empty, \{ϵ\}, \{a\} $$ are all RL
* Inductive step: Show that if the languages of $$ R_1, R_2 $$ are regular from closure property
  * $$ R_1 \cup R_2 $$
  * $$ R_1 \cdot R_2 $$
  * $$ R_1^* $$

> Proof How to remove a state

* Let $$ q_r $$ be a non-start, non-sccept state
* consider what sequences of states $$ q_r $$ appears in successful computations, might muiltple q's in a row
* but there will be some $$ q_i $$ directly before $$ q_r $$ and some $$ q_j $$ directly after it
* Add $$ R_1R_2^*R_3 $$ to the transition from $$ q_i $$ to $$ q_j $$
* $$ R_1R_2^*R_3 \cup R_4 $$

> Proof Add a state

* For a First step we add a new state as a accepted state
* and add $$ ϵ $$ to all accept tate

> Proof languages are regular

1. Give a DFA
1. Give a regular expression
1. Use closure properties $$ \cup, \cap, ^c, \cdot, * reverse $$

> Proof languages are not regular

* Show that language doesn't have a property that all RL have

* Consider a DFA M that contains p states
* take w a word of length >= p as an input
* $$ w = w_1w_2 ... w_n $$, n >=p
* Calculate the sequence of states $$ q_0q_1, ..., q_n $$ where $$ q_{i+1} = \delta(q_i, w_{i + 1}) $$
* this sequence contains n + 1 states and n + 1 > p, means that in the sequnce $$ q_0, ..., q_n $$ some state appears 1+
* Lets label that state as $$ q_i, q_j $$ in our sequence where i < j
* Pumping lemma
  * For any regular language L, there exists value p, called the pumping length
  * s.t. for any word $$ w \in L $$, s.t. $$ |w| \geq p $$ there exists a decomposition of w = xyz
  * x, y, z satisfy the $$ x(y)^iz \in L $$
    1. for any $$ i \geq 0 $$
    2. $$ |y| > 0 $$
    3. $$ |xy| \leq p $$
  * Contrapositive

> Diagonalization proof R’is uncountable

1. assume a one-to-one f from N to R’
1. construct x (in R’) based on f
1. show that x cannot correspond to any number in N

> $$ L = \{ 0 ^ n 1 ^ n : n \geq 0 \} $$

* Lemma 3 tells us that xy consists of all 0's (since the p chars of $$ 0^p1^p $$ are all 0's)

> Convert NFA to Regular language

![NFA diagram](images/20210423_170127.png)

$$ (a \cup b)^{*} c \cup(b \cup c)^{*} a \cup(c \cup a)^{*} b $$

> Prove that regular language is under following operations

$$ F(L) = \{a_1a_1a_2a_2...a_ka_k | a_1a_2...a_k \in L(a_i \in \Sigma) \} $$

* $$ Q` = Q \times (\{\$\} \cup \Sigma) $$
* $$ \delta((r, \$), x) = \{(r, x)\} $$ for all $$ r \in Q, x \in \Sigma $$
* $$ \delta((r, x), x) = \{\delta(r, x), \$ \} $$ for all $$ r \in Q, x \in \Sigma $$
* $$ \delta((r, x), y) = \empty $$ otherwise
* $$ q0' = (q0, \$) $$
* $$ F' = \{(r, \$) | r \in F \} $$

## DFA

![DFA](images/20210407_201518.png)

* Deterministic finite automation
* FSM that accepts or rejects a string of symbols, by running through a state sequence uniquely determined by string
* [-] don't have access to unbounded different memory states, can only read string once

| Term                                        | Meaning             |
| ------------------------------------------- | ------------------- |
| $$  Q  $$                                   | finite of states    |
| $$ \Sigma $$                                | finite alphabet     |
| $$ \sigma: Q \times \Sigma \rightarrow Q $$ | transition function |
| $$ q \in Q $$                               | start state         |
| $$ F \subseteq Q $$                         | set of accept state |

$$ q_i = \sigma(q_{i - 1}, w_i) $$

* accept if $$ q_n \in F $$
* reject if $$ q_n \notin F $$

> First Last character are different

![Binary String s.t. first and last character are different](images/20210411_164233.png)

> Contains at most 2 c's

![The set of strings in the alphabet {a, b, c} which contain at most 2 c’s](images/20210411_164302.png)

> Complement

![Language](images/20210515_065657.png)

![Complement of language](images/20210515_065708.png)

## NFA

* non-deterministic finite automata
* an NFA, $$ M = (Q, \Sigma, \delta, q_0, F) $$ on an input w
* accepts if a way of writing w as $$ w = w_1...w_n, w_i \in \Sigma_z $$ and a sequence of states

$$ q_0, ..., q_n, q_i \in Q $$, $$ q_{i + 1} \in \delta(q_i, w_{i+1}) $$ for all $$ 0 \leq i < n $$ and $$ q_n \in F $$

| Term         | Meaning        |
| ------------ | -------------- |
| $$ ϵ $$      | empty action   |
| $$ \sqcup $$ | disjoint union |

> Proof Closed under concatenation

* If R1, R2 are languages for NFAs
* $$ M_1 = (Q1, \Sigma, \delta_1, q_{0, 1}, F_1) $$
* $$ M_2 = (Q2, \Sigma, \delta_2, q_{0, 2}, F_2) $$

![Concatenation](images/20210409_230218.png)

* $$ M = L(m) = R1 \cdot R2 $$
* $$ M = (Q_1 \sqcup Q_2, \Sigma, q_{0, 1}, F_2) $$
* $$ \delta(q, ϵ) = \{q_{0, 2} \} \cup \delta_1(q_1 ϵ) $$
* $$ \delta(q, a) = \delta_1(q_1) \text{ if } q \in Q_1, q \in F_1 $$
* $$ \delta(q, a) = \delta_2(q ϵ) \text{ if } q \in Q_2 $$

> Proof conversion to DFA

* Keep track of all possible states the NFA can be in after reading k characters of the input

$$ M = (Q, \Sigma, \delta, q_0, F) $$
$$ M_D = (P(Q), Σ, \delta_d, \{ \text{all state reachable from q0 by } ϵ \}, \{S ⊆ Q : S \cap F \neq \empty \} ) $$

$$ δ_D : P(Q) \times \Sigma \rightarrow P(Q) $$
$$ δ_D(S, a) = \{\text{all states that reached from a state in S by 1, a-transition and any } ϵ \text{ transition} \} $$

![NFA](images/20210410_014227.png)
![Result DFA](images/20210410_014242.png)

> Find union of two NFA

![Question](images/20210423_201130.png)

![Answer in NFA / DFA](images/20210423_201144.png)

> Must convert to equivalent DFA in order to find complement

![Counter example of swapping accpet and reject state](images/20210515_065803.png)

## PDA

* Pushdown Automata: Read / Pop / Pushdown
* implemented memory using a stack (read top / add top / remove from top)
* [-] cannot use memory more than once, can't go through the input more than once

| symbol                                                             | meaning             |
| ------------------------------------------------------------------ | ------------------- |
| $$ \Gamma $$                                                       | Stack alphabet      |
| $$ δ : Q \times \Sigma_ϵ \times \Gamma_ϵ → P(Q \times \Gamma_ϵ) $$ | transition function |

* Given a PDA $$ M = (Q, Σ, Γ, δ, q_0, F) $$, M accepts $$ w \in \Sigma^* $$, if w can be written as $$ w = w_1w_2...w_n$$
* $$ \delta(start, read, pop) = () $$

* Multi character <-> Single character PDa

* Regular <-> Empty stack: Empty stack only accpets when stack is empty
  * ->: language L with regular PDA M, put an additional state that removes everything from the stack
  * <-: if we take M's as an empty-stack PDA, if will accept precisely the words accepted by M

* Closure properties on
  * under complementation
  * $$ \cup $$: create another state and connect them with ϵ
  * $$ \cdot $$: can put clearing state between M1 and M2
  * $$ ^* $$: Put # symbol from end to start

## CFG

* Context free Grammar is a 4 tuple ($$ V, \Sigma, R, S $$)
* V: a finite set of variables
* $$ \Sigma $$: a finite set of terminals and $$ V \cap \Sigma = \emptyset $$
* R: finiate set of rules which are pairs consiting of a single variable and string of variables and terminals
  * $$ (T \rightarrow W, T \in V, w \in (U \cup \Sigma )^*) $$
* S: start variable, $$ S \in V $$
* Every regular language has CFG

> Proof How does G describe words?

* start with S, and apply rules from R by replacing variable in rule with corresponding word in rule
  * (ex: $$ T \rightarrow W $$)

* We repeat until we get a string of terminals
* Then say that the resulting string of terminals was derived from S
* L(G) is the set of all derivations of S

> $$ \{ 0^n1^n : n \geq O \} $$

* $$ G = \{V, \Sigma, R, S \} $$
* $$ V = \{S\} $$
* $$ \Sigma = \{0, 1\} $$
* $$ R = \left\{\begin{array}{l} S \rightarrow 0S1 \\ S \rightarrow ϵ
\end{array}\right\} = \{ S \rightarrow 0S1 | ϵ \} = \{ 0^n1^n : n \geq 0 \} $$
* $$ S = S $$

> Proof PDA and CFG are equivalent

* M will be a empty-stack PDA that allow pushing transition function

$$ δ: Q \times \sum_{\varepsilon} \times \Gamma_{\varepsilon} → P(Q \times \Gamma^{\star}) $$

$$ δ\left(q_{1}, a, b\right)=\left\{\begin{array}{ll} \left\{\left(q_{1}, \varepsilon\right)\right\} & a=b(\in) \\
\{(q, u): b \rightarrow u \text{ is a rule in } R & b \in v, a = ϵ \\ \empty & \text{otherwise} \end{array}\right.  $$

> $$ (\{S\}, \{0, 1\}, \{S \rightarrow 0S1, 1S0, ϵ \}, S) $$

* Forwards as backwards

![CFG with 0S1, 1S0](images/20210429_032022.png)

> Show following language in set builder notation

$$ G_1 = (\{S\}, \{0, 1\}, R, S) $$
$$ S \rightarrow S0, S \rightarrow 1S, S \rightarrow ϵ $$
$$ \{ 1^n 1^m | n \geq 0, m \geq 0 \} $$

## CFL

* Context free language are the set of languages that have a CFG
* Closed under $$ \cup, \cdot, * $$
* Not closed under $$ \cap, ^c $$

> Proof CFLs are not closed under $$ \cap $$

* $$ L1 = 0^n1^n0^k: n, k >= 0 $$
* $$ L2 = 0^k1^n0^n: n, k >= 0 $$
* $$ L1 \cap L2 = 0^n1^n0^n $$

> Proof CFLs are not closed under $$ ^c $$

* Closure under $$ U + C \rightarrow $$ Closure under $$ \cap $$
* not closed under $$ \cap $$ -> not (closed under $$ \cup +  ^c $$)

> Proof there are strings that cannot be covered by CFL

* Consider counting them
* Claim: CFLs are countably infinite
* CFG/ PDA can be encoded as strings over a finite alphabet
* CFG is a 4-tuple $$ (V, \Sigma, R, S) $$, Fix $$ \Sigma $$, fix a set of characters used to describe variables

* A CFG can be thought of as a string over set $$ \{S, \_, 0, 1, 2, ..., 9 \rightarrow \{, \}, (, ), \} \cup \Sigma $$
* So CFL also has countably many strings

> Proof non-context-free language

* If we could give a context-free version of the pumping lemma
* ∃ a pumping length st if $$ w \in L $$ and $$ |w| \geq p $$, then w can be decomposed as $$ w = uvxyz $$ with followings

1. $$ uv^ixy^iz \in L $$ for all $$ i \geq 0 $$
1. $$ |vy| > 0 $$
1. $$ |vxy| \leq p $$

> $$ L = \{0^n1^n0^n\} $$ is not context-free language

* By contradiction, assume L is context-free, there exists a pumping length p
* Consider applying the the CFL pumping Lemma to the word $$ 0^p 1^p 0^p \in L $$
* $$ 0^p 1^p 0^p = uvxyz $$ for some strings $$ u, v, x, y, z $$ with $$ |vy| > 0 $$ and $$ |vxy| \leq p $$
* Taking $$ i = 0 $$ gives that $$ uxz \in h $$
* Since $$ |vy| > 0 $$, $$ | uxz| < 3p $$ Thus $$ uxz = 0^l1^l0^l $$ for some $$ l < p $$
* This means that v and y contained characters from the first p characters of $$ 0^p1^p0^p $$
* this means $$ vxy $$ contains all of the 1's of $$ 0^p1^p0^p $$ which implies $$ |vxy| > p $$, which is a contradiction

## TM

* Church–Turing thesis: Every algorithm has a Turing Machine
* Turing machine consists of 7 tuple $$ Q, \Sigma, \Gamma ,\delta, q_0, q_{accept}, $$
* Have tape and allow head move left or right
* Rpeat until we get to $$ q_{accept} $$ or $$ q_{reject} $$
* Don't require TMs to acctually every reach $$ q_{accept} / q_{reject} $$, it's possible that it falls on infinite loop

| Term                                                                      | Meaning               |
| ------------------------------------------------------------------------- | --------------------- |
| $$ Q $$                                                                   | finite states         |
| $$ \Sigma : \_ \notin \Sigma$$                                            | finite input alphabet |
| $$ \Gamma : \_ \in \Gamma $$                                              | finite tape alphabet  |
| $$ \sigma: Q \times \Gamma \rightarrow Q \times \Gamma \times \{L, R\} $$ | transition function   |
| $$ q_0 \in Q $$                                                           | start state           |
| $$ q_{accept} \in Q $$                                                    | accept state          |
| $$ q_{reject} \subseteq Q $$                                              | reject state          |

| Term          | Meaning                                                            |
| ------------- | ------------------------------------------------------------------ |
| <>            | { \<G> : G is a finite simple Connected Graph }                    |
| $$ A_{xx} $$  | { <M, W> : $$  w \in L(M)$$ : M is a machine of type xx }          |
| $$ E_{xx} $$  | { \<M> :$$ L(M) = \empty$$ : M is a machine of type xx }           |
| $$ E_{qxx} $$ | { <M, N> :$$ L(M, N) = \empty $$ : M, N are a machine of type xx } |

> Types

![Language](images/20210512_041649.png)

* Turing decidable: has is a decider for the language, always halt
  * closed under union, intersection, and complement
  * There is no general way to prove whether a given machine halts on all inputs
  * iff it and its complement are both recognizable
* Turing recognizable: if there is a TM for the language
  * closed under union, intersection
  * Complement of $$ A_{TM} $$ is unrecognizable
* Deciders: TM that always halts
* Turing-corecognizable: $$ L^c $$ recognizable

> Proof Decidable languages are closed under union

* Let L1 and L2 be languages over Σ and suppose M1 and M2 are TMs deciding these languages
* define a new TM, M, via a high-level description
  1. Run M1 on input w. If M1 accept w, accept. Otherwise go to 2
  2. Run M2 on input w. If M2 accept w, accept. Otherwise reject
* then show that L(M) = L1 U L2 and that M always halts

> State Diagram of $$ 0^n1^n0^n, where n > 0 $$

![State diagram](images/20210507_013911.png)

> Proof: $$ EQ_{DFA} $$ is decidable

* $$ EQ_{DFA} = \{ <M, N>: L(M) = L(N), M, N, DFAs \} $$

* Check inputs to see if M and N both accept or both reject, if some input rejects on are accepts on the other, reject
  * This won't let accept inputs

1. Check if input is of the form <M, N>, if not reject
1. Construct a DFA for $$ [L(m)^c \cap L(N)] \cup [L(m) \cap L(N)^c] $$
1. Run the decider for $$ E_{TM} $$ on input \<p\>

* From $$ E_{DFA} $$ we can check if the language of a machine is empty
* Can relate $$ L(M)= L(N) $$ to the language of some machine being empty?

> Proof: $$ A_{TM} $$ is Turing-recognizable

1. Type-check if our input is of the form <M, W> for some TM M and input W, if not reject
1. Run M an input w, accepts if it accepts
1. Run M on input w -> this isn't a decider since this step doesn't halt in general

> Proof: $$ A_{TM} $$ is undecidable

* Towards contradiction that $$ A_{TM} $$ is decidable
* Let H be a decider for $$ A_{TM} $$
  * H accepts inputs of the form \<M, W> if $$ w \in L(M) $$ and rejects these inputs if $$ w \notin L(M) $$

* Define a TM D as follows

1. Type check if input is of the form \<M> for some TM M, reject if not
1. Run H on input \<M, \<M>>, accept if H rejects, reject if H accept

* Find a contradiction
  * What happens if we run D on \<D>

1. Type-check \<D>
1. Run H on input \<D, \<D>
    * H accepts \<D, \<D>> -> we reject
    * H rejects \<D, \<D>> -> we reject

> Proof if a language L and its complement are both recognizable, then L is decidable

* let $$ M_1 $$, be a recognizer for L, and $$ M_2 $$ be a recognizer for $$ L^c $$, then we can define a TM M as follows
* On input w: Alternate running w on $$ M_1 $$ and $$ M_2 $$, as soon as one halts halt
* If $$ M_1 $$ halted and accepted, accept
* If $$ M_1 $$ halted and rejected, reject
* If $$ M_2 $$ halted and accepted, reject
* If $$ M_2 $$ halted and rejected, accept

* M is a decider and $$ L(M) = L $$
* (L recognizable and $$ L^c$$ recognizable) $$ \rightarrow $$ L decidable
* L undecidable $$ \rightarrow \neg $$ (L recognizable and $$ L^c $$ recognizable)
* L undecidable $$ \rightarrow $$ (L unrecognizable or $$ L^c $$ unrecognizable)

## Reduction

* Given a computational problem A convert / reduce it to a computational problem B, then find a function f, s.t

$$ w \in A \leftrightarrow f(w) \in B $$

* f is a TM, we take contents of the tape when it halts (must be decider)

$$ f = \Sigma^\star \rightarrow \Sigma ^ \star $$

* s.t. there is a decider $$ M_f $$ such that an input w, f halts with f(x) on its tape

| -                   | $$ A \leq_r B $$ | $$ A \leq_m B $$    |
| ------------------- | ---------------- | ------------------- |
| B is decidable      | A is decidable   | A is decidable      |
| B is recognizable   | X                | A is recognizable   |
| A is undecidable    | A is undecidable | A is undecidable    |
| A is unrecognizable | B is undecidable | B is unrecognizable |

> Terms

* Computable function: any programmable procedure that takes input x and outputs f(x)
* Rice Theorem: Any language of the form {\<M>| L(M) has property P} is undecidable for any non-trivial property P
  * non-trivial property: some TM have, others don't (ex: is language context free, is empty)
* Turing reudce: written as $$ A \leq_m B $$
* Mapping reduce: written as $$ A \leq_m B $$ (A is not harder than B)
  * A computational problem A mapping reduces to a computational problem B if there exists a computation function f s.t

$$ w \in A \leftrightarrow f(x) \in B $$ for all $$ w \in \Sigma^* $$

* $$ HALT_{TM} $$: {<M, w> | M is a TM and M halts on input w}
  * $$ HALT_{TM} \leq_m A_{TM} $$, $$ A_{TM} \leq_m HALT_{TM} $$

> Proof undecidability

* Problem X is undecidable
  1. Show that $$ A_{TM} $$ reduces to X
  2. SHOW that $$ HALT_{TM} $$ reduces to X
* In each of these, have access to Genie which can answer question about X

> Proof Rice Theorem by contradiction

* Let $$ L_P = $$ {\<M\> | L(M) has property P}
* Suppose that there exists at least one TM in $$ L_p $$, call it N
* Design reduction function F: on input x
* Typecheck x = \<M, w>
* Build Machine M': on input z:
  * Run M on w: if M accepts w then accepts
* Output \<M'>

> Reducing $$ A_{TM} $$ to $$ \overline{E_{TM}} $$

* $$ \overline{E_{TM}} $$ is not easier than $$ A_{TM} $$
* if $$ A_{TM} $$ is undecidable than $$ \overline{E_{TM}} $$
* We can build a decider for $$ A_{TM} $$
  * On input <M, w>, use F(<M, w>) to construct M'
  * Run $$ M_E $$ on <M'>, if accept then accept, if rejects then reject
* Therefore there cannot be a decider for $$ \overline{E_{TM}} $$

> $$ HALT_{TM} $$ can be used to solve $$ A_{TM} $$

* Given: Turing machine M, string w, magic genie for $$ HALT_{TM} $$
* Goal: Using Genie, construct a decider for $$ A_{TM} $$

1. On input <M, w> ask Genie about M and w
2. If Genie says no, then reject; if Genie says yes, run M on w
  a. if computation accepts, accepts / rejects reject
3. Output <M', w>
