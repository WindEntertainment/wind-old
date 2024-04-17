#!/bin/bash

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

if [[ $with_asset_bundler ]]; then
  wm run install-asset-bundler --root "$root" -b "$build_type"
  wm run run-asset-bundler --root "$root" -b "$build_type"
fi

wm run install-game --root "$root" -b "$build_type"
