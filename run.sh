#!/bin/bash

if [ $# -eq 0 ];
then
  echo "$0: Missing arguments"
  exit 1
else
  clang++ -fsanitize=undefined $1/tests.cpp
  ./a.out
  clang++ -fsanitize=address $1/tests.cpp
  ./a.out
  clang++ -fsanitize=leak $1/tests.cpp
  ASAN_OPTIONS=detect_leaks=1 LSAN_OPTIONS=suppressions=lsan.supp ./a.out
  rm -rf a.out
fi