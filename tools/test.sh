#!/bin/bash

source "$(dirname "$0")/global.sh"

with_coverage=false
with_dependencies=false

root=""

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -wc|--with-coverage) with_coverage=true; ;;
    -wd|--with-dependencies) with_dependencies=true; ;;
    --root) root="$2"; shift; ;;
    *) echo "Unknown parameter passed: $1"; exit; ;;
  esac
  shift
done

cd "$root" || exit

if [[ $with_dependencies = true ]]; then
  rm -rf build
  wm run conan-install -bt Debug
  wm run cmake-configure --build-type Debug --with-testing
fi

cd "$root/build/Debug/tests" || exit

make
ctest

if [[ $with_coverage = true ]]; then
  cd "../" || exit
  make coverage
fi

cd "$root" || exit
