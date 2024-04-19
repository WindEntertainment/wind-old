#!/bin/bash
set -e -o errtrace

trap_error() {
  echo "ERROR: ${BASH_SOURCE[1]} at ${BASH_LINENO[0]}"
}
trap trap_error ERR

throw() {
  local status=${1:-2}
  local message="$2"

  if [[ -n $message ]]; then
    echo "Error: $message"
  fi

  exit "$status"
}
