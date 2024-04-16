#!/bin/bash

initial_root_dir=$(pwd)
root_dir=""
relative_root_dir=""

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -r|--root) relative_root_dir="$2"; shift ;;
    -b|--build-type) build_type="$2"; shift ;;
    *) echo "Unknown parameter passed: $1"; exit 1 ;;
  esac
  shift
done

if [[ -n "$relative_root_dir" ]]; then
  cd "$relative_root_dir" || { echo "Error: Unable to change directory to $relative_root_dir"; exit 1; }
  root_dir=$(pwd)
fi

cd game/data

rm -rf .cache
wind-asset-bundler -b main
rm -rf .cache
wind-asset-bundler -b resources
rm -rf .cache

cd $initial_root_dir
