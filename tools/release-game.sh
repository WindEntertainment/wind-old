#!/bin/bash

source "$(dirname "$0")/global.sh"

build_type="Release"
output_folder="releases"
clear_output_folder=true

call_dir=$(pwd)
root=""

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -b|--build-type) build_type="$2"; shift ;;
    -o|--output) output_folder="$2"; shift ;;
    -r|--root) root="$2"; shift ;;
    -c|--clear-output-folder) clear_output_folder=false; shift;;
    *) echo "Unknown parameter passed: $1"; exit 1 ;;
  esac
  shift
done

cd "$root/build/$build_type" || exit

if [ "$OS" != "Windows" ]; then
  if [[ $clear_output_folder ]]; then
    sudo rm -rf "$output_folder" || echo ""
  fi
fi

cpack -B "$root/$output_folder"

cd "$call_dir" || exit
