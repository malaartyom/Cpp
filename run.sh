#!/bin/bash

if [ $# -eq 0 ];
then
  echo "$0: Missing arguments"
  exit 1
else
  clang++ -std=c++2a $1/tests.cpp
  ASAN_OPTIONS=detect_leaks=1 LSAN_OPTIONS=suppressions=lsan.supp ./a.out
  rm -rf a.out
fi
# brew link llvm@8
#  -fsanitize=undefined -fsanitize=address -fsanitize=leak $1/tests.cpp
