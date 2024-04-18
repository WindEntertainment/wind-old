#!/bin/bash

initial_path=$(pwd)

if [ ! -f "wm" ]; then
  echo "Error: The 'wm' script does not exist in the directory."
  exit 1
fi

echo "$OS"
symlink_origin_path="$(pwd)/wm"
if echo "$OS" | grep -qi "Windows"; then
  symlink_path='C:\Program Files\wm'

  if [ ! -d "$symlink_path" ]; then
    mkdir -p "$symlink_path"
  fi

  # ln -sf "$symlink_origin_path" "$symlink_path"
  # Create the shortcut using PowerShell
  powershell -Command "New-Object -ComObject WScript.Shell).CreateShortcut(\"$symlink_path\\wm.lnk\").TargetPath = \"$symlink_origin_path\""


  bash_path="/c/Program Files/wm"
  bash_profile="$HOME/.bash_profile"
  if [ -f "$bash_profile" ]; then
      echo "export PATH=\"\$PATH:$bash_path\"" >> "$bash_profile"
      echo "Updated PATH variable in $bash_profile"
  else
      echo "export PATH=\"\$PATH:$bash_path\"" > "$bash_profile"
      echo "Created $bash_profile with updated PATH variable"
  fi

  source "$bash_profile"
else
  sudo chmod +x wm

  symlink_path='/usr/local/bin/wm'

  if [ ! -d "$symlink_path" ]; then
    mkdir -p "$symlink_path"
  fi

  ln -sf "$symlink_origin_path"  $symlink_path
fi

echo "wm configured!"

cd "$initial_path" || exit
