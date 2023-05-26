#!/bin/bash

tmp1=0
find "$(pwd)" -type f | egrep '^.+[^/]\.[a-zA-Z0-9]{1,}$' | sed -r 's/^.*\.([^.]+)$/\1/' | tr “[:upper:]” “[:lower:]” | awk '{ ext[$1]++} END { for (e in ext) tmp1++; print tmp1; for (e in ext) print e }' | sort -nr

