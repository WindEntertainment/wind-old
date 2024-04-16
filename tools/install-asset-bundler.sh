#!/bin/bash

initial_root_dir=$(pwd)
root_dir=""
relative_root_dir=""
build_type="Release"
os=Unknown

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

case "$(uname)" in
  Linux*)   os="Linux";;
  Darwin*)  os="MacOS";;
  CYGWIN*)  os="Windows";;
  MINGW*)   os="Windows";;
  *)        os="Unknown";;
esac

echo "Operating System: $os"
echo "Build type: $build_type"
echo "Root directory: $root_dir"

if [[ $os == "Unknown" ]]; then
  echo "Unknown OS"
  exit 1
fi

conan install . --build=missing -s build_type=$build_type

cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="$build_type" -DCMAKE_TOOLCHAIN_FILE="$root_dir/build/$build_type/generators/conan_toolchain.cmake" -S"$root_dir" -B"$root_dir/build/$build_type"

cmake --build "$root_dir/build/$build_type" --parallel 10 --target wind-asset-bundler

cd build/$build_type/wind/asset-pipeline

make install

cd $initial_root_dir
