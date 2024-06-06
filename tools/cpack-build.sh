#!/bin/bash

source "$(dirname "$0")/global.sh"

build_type="Release"
output_folder="releases"

call_dir=$(pwd)
root=""

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -bt|--build-type) build_type="$2"; shift ;;
    -o|--output) output_folder="$2"; shift ;;
    --root) root="$2"; shift ;;
    *) echo "Unknown parameter passed: $1"; exit 1 ;;
  esac
  shift
done

cd "$root/build/$build_type" || exit

cpack -B "$root/$output_folder"

cd "$call_dir" || exit
