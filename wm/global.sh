#!/bin/bash

CONFIG_NAME="wm-config.yml"
SCRIPTS_FOLDER_CONFIG_KEY="scriptsFolder"
DEFAULT_SCRIPTS_FOLDER="tools"

find_config() {
  start_dir="$(pwd)"

  while [ "$start_dir" != "/" ]; do
    if [ -f "$start_dir/$CONFIG_NAME" ]; then
      echo "$start_dir"
      return 0
    fi
    start_dir=$(dirname "$start_dir")
  done

  echo "Error: No $CONFIG_NAME found in or above the current directory" >&2
  exit 1
}

get_scripts_folder() {
  config_folder="$1"

  scripts_folder=$(yq e .$SCRIPTS_FOLDER_CONFIG_KEY "$(find_config)/$CONFIG_NAME")

  if [ ! -d "$config_folder/$scripts_folder" ]; then
    echo "Error: Scripts folder '$config_folder/$CONFIG_NAME' not found"
    exit 1
  fi

  echo "$config_folder"/"$scripts_folder"
}
