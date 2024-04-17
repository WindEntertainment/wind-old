#!/bin/bash

if [ ! -f "wm" ]; then
  echo "Error: The 'wm' script does not exist in the directory."
  exit 1
fi

echo "$OS"
if echo "$OS" | grep -qi "Windows"; then
  new_path="$(pwd)\wm"
  echo "$new_path"

  user_home="$HOME"

  cd "$user_home" || exit 1

  bashrc_file="$user_home/.bashrc"

  if [ -f "$bashrc_file" ]; then
    echo "export PATH=\$PATH$new_path" >> "$bashrc_file"
    echo "Updated PATH in $bashrc_file"
  else
    echo "Error: .bashrc not found in $user_home"
  fi
else
  sudo chmod +x wm
  ln -sf "$(pwd)/wm" /usr/local/bin/wm
fi

echo "wm configured!"
