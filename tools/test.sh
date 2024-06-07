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
  wm run cmake-build --build-type Debug --target tests --with-testing
  wm run cmake-build --build-type Debug --target game-tests --skip-configure
  wm run cmake-build --build-type Debug --target wind-tests --skip-configure
fi

cd "$root/build/Debug/tests" || exit

ctest

cd "$root" || exit
