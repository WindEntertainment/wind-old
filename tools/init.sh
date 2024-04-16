#!/bin/bash

for file in *.sh; do
  if [ -f "$file" ]; then
    sudo chmod +x "$file"
    echo "Added execute permission to: $file"
  fi
done
