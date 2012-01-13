#!/bin/bash
COUNT=$(cat lines.in|wc -l)
for i in $( seq 1 1 $COUNT ); do head -n$i lines.in|./lines|tac >tmp; sleep 0.5; clear; cat tmp; done
