#!/bin/bash

source "$(dirname "$0")/global.sh"

build_type="Release"
skip_build=false

call_dir=$(pwd)
root=""

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -bt|--build-type) build_type="$2"; shift ;;
    -sb|--skip-build) skip_build=true; ;;
    --root) root="$2"; shift ;;
    *) echo "Unknown parameter passed: $1"; exit 1 ;;
  esac
  shift
done

cd "$root" || exit 2

if [[ $skip_build = false ]]; then
  wm run cmake-build --build-type "$build_type" --target wind-asset-bundler
fi

cd build/"$build_type"/wind/core/asset-pipeline || exit 2

if echo "$OS" | grep -qi "Windows"; then
  mkdir -p "$root"/apps
  make install DESTDIR="$root"/apps
  ls -a "$root"/apps/usr/local/bin
else
  make install
fi

cd "$call_dir" || exit 2
