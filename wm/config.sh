#!/bin/bash

if [ ! -f "wm" ]; then
  echo "Error: The 'wm' script does not exist in the directory."
  exit 1
fi

sudo chmod +x wm

ln -sf "$(pwd)/wm" /usr/local/bin/wm

echo "wm configured!"
