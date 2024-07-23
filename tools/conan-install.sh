#!/bin/bash

source "$(dirname "$0")/global.sh"

build_type=Release

call_dir=$(pwd)
root=""

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -bt|--build-type) build_type="$2"; shift; ;;
    --root) root="$2"; shift; ;;
    *) echo "Unknown parameter passed: $1"; exit; ;;
  esac
  shift
done

cd "$root" || exit

conan install . --build=all -s build_type="$build_type"

cd "$call_dir" || exit
