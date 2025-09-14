# Initial design

A finite autotomata $M$ is a 5-tuple $(Q, \Sigma, \delta, q_0, F)$, where

- $Q$ is a set of states,
- $\Sigma$ is an alphabet,
- $\delta$ is a transition function $\delta : Q \times \Sigma \to Q$,
- $q_0 \in Q$ is the start state, and
- $F \subseteq Q$ is the set of accept states.

```text
automata {
    states : set
    alphabet : set 
    transition_func : table
    start_state : set_member
    accept_states : set
}
```

## Sample Input

```text
1 -> 2 : a
2 -> 3 : b
1
3
```
