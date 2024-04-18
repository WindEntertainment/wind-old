#!/bin/bash

source "$(dirname "$0")/global.sh"

with_asset_bundler=false
build_type="Release"

root=""

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -b|--build-type) build_type="$2"; shift ;;
    -w|--with-asset-bundler) with_asset_bundler=true; shift ;;
    -r|--root) root="$2"; shift ;;
    *) echo "Unknown parameter passed: $1"; exit 1 ;;
  esac
  shift
done

cd "$root" || exit

conan install . --build=missing -s build_type="$build_type"

if [[ $with_asset_bundler ]]; then
  wm run build-asset-bundler --root "$root" -b "$build_type"
  wm run run-asset-bundler --root "$root"
fi

wm run build-game --root "$root" -b "$build_type"
