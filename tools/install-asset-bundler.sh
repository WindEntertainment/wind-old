#!/bin/bash

build_type="Release"

call_dir=$(pwd)
root=""

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -b|--build-type) build_type="$2"; shift ;;
    -r|--root) root="$2"; shift ;;
    *) echo "Unknown parameter passed: $1"; exit 1 ;;
  esac
  shift
done

cd "$root" || exit

conan install . --build=missing -s build_type="$build_type"

cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="$build_type" -DCMAKE_TOOLCHAIN_FILE="$root/build/$build_type/generators/conan_toolchain.cmake" -S"$root" -B"$root/build/$build_type"

cmake --build "$root/build/$build_type" --parallel 10 --target wind-asset-bundler

cd build/"$build_type"/wind/asset-pipeline || exit

make install

cd "$call_dir" || exit
