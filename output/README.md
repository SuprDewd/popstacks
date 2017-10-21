# Popstacks DFA

This directory contains the final deterministic finite automata produced by the programs in the parent directory. For each `k`, `dfa_k.txt` recognizes the language consisting of sorting plans of order `k`. See our [paper](https://arxiv.org/abs/1710.04978) for relevant information.

If a DFA has `N` states, `M` transitions, `F` accept states and initial state `K`, then the corresponding DFA file has the following format. Note that the states are labeled from `0` to`N-1`. The first line has the form:
> N M K F

Then follow `M` lines, each of the form
> A L B

denoting a transition from state `A` to state `B` with label `L`.
Finally, `F` lines follow, each with the label of an accepting state.
