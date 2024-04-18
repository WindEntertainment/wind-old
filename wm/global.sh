#!/bin/bash
set -e -o errtrace

trap_error() {
  echo "ERROR: ${BASH_SOURCE[1]} at ${BASH_LINENO[0]}"
}
trap trap_error ERR

CONFIG_NAME="wm-config.yml"
SCRIPTS_FOLDER_CONFIG_KEY="scriptsFolder"
DEFAULT_SCRIPTS_FOLDER="tools"

throw() {
  local status=${1:-2}
  local message="$2"

  if [[ -n $message ]]; then
    echo "Error: $message"
  fi

  exit "$status"
}

find_config() {
  start_dir="$(pwd)"

  while [ "$start_dir" != "/" ]; do
    if [ -f "$start_dir/$CONFIG_NAME" ]; then
      echo "$start_dir"
      return 0
    fi
    start_dir=$(dirname "$start_dir")
  done

  throw 1 "No $CONFIG_NAME found in or above the current directory"
}

get_scripts_folder() {
  config_folder="$1"

  scripts_folder=$config_folder/$(yq e .$SCRIPTS_FOLDER_CONFIG_KEY "$config_folder/$CONFIG_NAME")

  [ ! -d "$scripts_folder" ] && throw 1 "Scripts folder '$scripts_folder' not found"

  echo "$scripts_folder"
}
