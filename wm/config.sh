#!/bin/bash

source "$(dirname "$0")/global.sh"

initial_path=$(pwd)

if [ ! -f "wm" ]; then
  echo "Error: The 'wm' script does not exist in the directory."
  exit 1
fi

echo "$OS"

if echo "$OS" | grep -qi "Windows"; then
  bash_profile="$HOME/.bash_profile"
  if [ -f "$bash_profile" ]; then
    echo "export PATH=\"\$PATH:$(pwd)\"" >> "$bash_profile"
    echo "Updated PATH variable in $bash_profile"
  else
    echo "export PATH=\"\$PATH:$(pwd)\"" > "$bash_profile"
    echo "Created $bash_profile with updated PATH variable"
  fi

  source "$bash_profile"
else
  symlink_origin_path="$(pwd)/wm"
  sudo chmod +x wm

  symlink_path='/usr/local/bin/wm'

  if [ ! -d "$symlink_path" ]; then
    mkdir -p "$symlink_path"
  fi

  ln -sf "$symlink_origin_path"  $symlink_path

  for file in "$(dirname "$0")"/*.sh; do
    if [ -f "$file" ]; then
      sudo chmod +x "$file"
      echo "Added execute permission to: $file"
    fi
  done
fi

echo "wm configured!"

cd "$initial_path" || exit
