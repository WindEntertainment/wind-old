#!/bin/bash

source "$(dirname "$0")/global.sh"

skip_build=false
with_coverage=false
with_dependencies=false

root=""

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -sb|--skip-build) skip_build=true; ;;
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
fi

if [[ $skip_build = false ]]; then
  wm run cmake-build --build-type Debug --target tests --with-testing
  wm run cmake-build --build-type Debug --target game-tests --with-testing
  wm run cmake-build --build-type Debug --target wind-tests --with-testing
fi

cd "$root/build/Debug/tests" || exit

ctest

if [[ $with_coverage = true ]]; then
  cd "../" || exit
  make
  make coverage
fi

cd "$root" || exit
