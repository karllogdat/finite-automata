# Finite Automata Simulator

A finite autotomata $M$ is a 5-tuple $(Q, \Sigma, \delta, q_0, F)$, where

- $Q$ is a set of states,
- $\Sigma$ is an alphabet,
- $\delta$ is a transition function $\delta : Q \times \Sigma \to Q$,
- $q_0 \in Q$ is the start state, and
- $F \subseteq Q$ is the set of accept states.

## Initial Design

This is subject to change.

```text
automata {
    states : set
    alphabet : set 
    transition_func : table
    start_state : set_member
    accept_states : set
}
```

## Sample Input File

```text
1 -> 2 : a
2 -> 3 : b
1
3
```

`1 -> 2 : a` represents a transition from state `1` to `2` whenever
the symbol `a` is read. An input file can have any number of these
"transition lines".

`1` is the start state of the machine. A machine can only have one
starting state.

`3` represents the accept states. Accept states are not limited
to a single state. For multiple accept states, add states in the
same line separated by whitespace.

For example, if I want a machine whose accept states are `1`, `2`,
and `3`, the last line would be:

```text
1 2 3
```

## Build Instructions

```sh
# clean bin directory
rm -rf ./bin
mkdir ./bin

gcc -o ./bin/main ./src/*.c
```

## Run Instructions

```sh
./bin/main <file>
```

Where `<file>` follows the sample input file above.
