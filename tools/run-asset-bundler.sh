#!/bin/bash

source "$(dirname "$0")/global.sh"

call_dir=$(pwd)
root=""

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -r|--root) root="$2"; shift ;;
    *) echo "Unknown parameter passed: $1"; exit 1 ;;
  esac
  shift
done

cd "$root"/game/data || exit

wind-asset-bundler -b main
wind-asset-bundler -b resources

cd "$call_dir" || exit
