#!/bin/bash

source "$(dirname "$0")/global.sh"

with_build=false

root=""

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -w|--with-build) with_build=true; ;;
    -r|--root) root="$2"; shift; ;;
    *) echo "Unknown parameter passed: $1"; exit; ;;
  esac
  shift
done

cd "$root" || exit

if [[ $with_build = true ]]; then
  wm run install -w -b Debug
fi

cmake --build "$root/build/Debug/tests"

cd "$root/build/Debug" || exit

ctest

make coverage

cd "$root" || exit
