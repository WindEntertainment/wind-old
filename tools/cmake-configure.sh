#!/bin/bash

source "$(dirname "$0")/global.sh"

build_type=Release

call_dir=$(pwd)
root=""

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -bt|--build-type) build_type="$2"; shift ;;
    --root) root="$2"; shift ;;
    *) echo "Unknown parameter passed: $1"; exit 1 ;;
  esac
  shift
done

cd "$root" || exit

if echo "$OS" | grep -qi "Windows"; then
  cmake -G "Unix Makefiles" -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DCMAKE_BUILD_TYPE="$build_type" -DCMAKE_TOOLCHAIN_FILE="$root/build/$build_type/generators/conan_toolchain.cmake" -S"$root" -B"$root/build/$build_type"
else
  cmake -G "Unix Makefiles" -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DCMAKE_BUILD_TYPE="$build_type" -DCMAKE_TOOLCHAIN_FILE="$root/build/$build_type/generators/conan_toolchain.cmake" -S"$root" -B"$root/build/$build_type"
fi

cd "$call_dir" || exit
