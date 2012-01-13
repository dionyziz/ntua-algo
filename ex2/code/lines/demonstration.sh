#!/bin/bash
for i in $( seq 1 1 100 ); do head -n$i lines.in|./lines|tac >tmp; sleep 0.5; clear; cat tmp; done
