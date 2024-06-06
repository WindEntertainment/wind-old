#!/bin/bash

source "$(dirname "$0")/global.sh"

build_type="Release"
target="game"
skip_configure=true

call_dir=$(pwd)
root=""

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -sc|--skip-configure) skip_configure=false; ;;
    -bt|--build-type) build_type="$2"; shift ;;
    -t|--target) target="$2"; shift ;;
    --root) root="$2"; shift ;;
    *) echo "Unknown parameter passed: $1"; exit 1 ;;
  esac
  shift
done

if [[ $skip_configure = true ]]; then
  wm run cmake-configure --build-type "$build_type"
fi

cd "$root" || exit

cmake --build "$root/build/$build_type" --parallel 10 --target "$target"

cd "$call_dir" || exit
