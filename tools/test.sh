#!/bin/bash

source "$(dirname "$0")/global.sh"

skip_build=false

root=""

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -sb|--skip-build) skip_build=true; ;;
    --root) root="$2"; shift; ;;
    *) echo "Unknown parameter passed: $1"; exit; ;;
  esac
  shift
done

cd "$root" || exit

if [[ $skip_build = false ]]; then
  wm run cmake-build --build-type "Debug" --target tests
  wm run cmake-build --build-type "Debug" -sc --target game-tests
  wm run cmake-build --build-type "Debug" -sc --target wind-tests
fi

cd "$root/build/Debug/tests" || exit

ctest

cd "$root" || exit
