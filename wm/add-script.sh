#!/bin/bash

source "$(dirname "$0")/global.sh"

call_dir=$(pwd)
root=""
name="script"

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -n|--name) name="$2"; shift ;;
    -r|--root) root="$2"; shift ;;
    *) echo "Unknown parameter passed: $1"; exit 1 ;;
  esac
  shift
done

cd "$root" || exit

file="$(get_scripts_folder "$root")/$name.sh"

[ -f "$file" ] && throw 1 "File $file already exists"

cp "$(dirname "$0")/health.sh" "$file"

[ ! -f "$file" ] && throw 1 "File $file not created"


if [ "$OS" != "Windows" ]; then
  if [ -f "$file" ]; then
    sudo chmod +x "$file"
    echo "Added execute permission to: $file"
  fi
fi

cd "$call_dir" || exit
