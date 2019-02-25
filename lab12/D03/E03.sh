#!/bin/bash
# Fanti Andrea 235808
# lab 12 exercise 03

cat "$1" | tr -s '[:space:]' '\n' | sort | uniq -c
