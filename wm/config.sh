#!/bin/bash

initial_path=$(pwd)

if [ ! -f "wm" ]; then
  echo "Error: The 'wm' script does not exist in the directory."
  exit 1
fi

echo "$OS"
if echo "$OS" | grep -qi "Windows"; then
  new_path="$(pwd)/wm"
  echo "$new_path"

  if [ -f ~/.bashrc ]; then
    echo "export PATH=\$PATH$new_path" >> ~/.bashrc
    echo "Updated PATH in ~/.bashrc"
  else
    cd ~/ || exit
    touch .bashrc
    echo "export PATH=\$PATH$new_path" >> ~/.bashrc
    echo "Created PATH in ~/.bashrc"
  fi
else
  sudo chmod +x wm
  ln -sf "$(pwd)/wm" /usr/local/bin/wm
fi

echo "wm configured!"

cd "$initial_path" || exit
