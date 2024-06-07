#!/bin/bash

source "$(dirname "$0")/global.sh"

[ -f "$CONFIG_NAME" ] && throw 0 "Config file already exists: $(pwd)/$CONFIG_NAME"

config=$(cat <<EOF
name: example
$SCRIPTS_FOLDER_CONFIG_KEY: $DEFAULT_SCRIPTS_FOLDER
EOF
)

echo "$config" > wm-config.yml

echo "Config initialised: $(pwd)/wm-config.yml"

mkdir "$DEFAULT_SCRIPTS_FOLDER"

cp "$(dirname "$0")/health.sh" "$(pwd)/$DEFAULT_SCRIPTS_FOLDER"

if echo "$OS" | grep -qi "Windows"; then
  for file in "$DEFAULT_SCRIPTS_FOLDER"/*.sh; do
    if [ -f "$file" ]; then
      sudo chmod +x "$file"
      echo "Added execute permission to: $file"
    fi
  done
fi

echo "Added base command to $(pwd)/$DEFAULT_SCRIPTS_FOLDER"

echo "Initialized successfully"
