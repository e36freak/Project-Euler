#!/bin/bash

for ((y = 1901; y <= 2000; y++)); do
  cal -vy "$y"
done | awk '
  $1 == "Su" {
    for (f = 2; f <= NF; f++) {
      if ($f == "1") {
        total++;
      }
    }
  }
  END {
    print total;
  } '
