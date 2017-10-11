#!/usr/bin/env bash
K=$1

SAGE='sage'
# SAGE='docker run -t -i sagemath/sagemath sage'

mkdir -p output
python gen_forbidden_subfigures.py $K | python dfa_for_all_patterns.py $K 0 1 > output/dfa_${K}.txt
${SAGE} -c "$(python dfa_to_gf.py $K < output/dfa_${K}.txt)"

