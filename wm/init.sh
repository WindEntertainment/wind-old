#!/bin/bash

source "$(dirname "$0")/global.sh"

if [ -f "$CONFIG_NAME" ]; then
  echo "Config file already exists: $(pwd)/$CONFIG_NAME"
  exit 0
fi

config=$(cat <<EOF
name: example
$SCRIPTS_FOLDER_CONFIG_KEY: $DEFAULT_SCRIPTS_FOLDER
EOF
)

echo "$config" > wm-config.yml

echo "Config initialised: $(pwd)/wm-config.yml"

mkdir "$DEFAULT_SCRIPTS_FOLDER"

cp" $(dirname "$0")/health.sh" "$(pwd)/$DEFAULT_SCRIPTS_FOLDER"

for file in $DEFAULT_SCRIPTS_FOLDER/*.sh; do
  if [ -f "$file" ]; then
    sudo chmod +x "$file"
    echo "Added execute permission to: $file"
  fi
done

echo "Added base command to $(pwd)/$DEFAULT_SCRIPTS_FOLDER"

echo "Initialized successfully"
