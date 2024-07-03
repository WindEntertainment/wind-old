#!/bin/bash

source "$(dirname "$0")/global.sh"

call_dir=$(pwd)
root=""

project=game

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -p|--project) project="$2"; shift ;;
    --root) root="$2"; shift ;;
    *) echo "Unknown parameter passed: $1"; exit 1 ;;
  esac
  shift
done

generate_folder_schemas() {
  source_folder=$1
  output_folder=$2
  language=$3

  project_dir=$(pwd)

  cd "$root"/type-generator

  for file in "$source_folder"/*.json; do
    if [ -f "$file" ]; then
      filename=$(basename -- "$file")
      filename_without_extension=$(basename -- "$file" | cut -f 1 -d '.')

      pnpm generate -l "$language" -o "$output_folder"/"$filename_without_extension" -s "$source_folder"/"$filename" &
    fi
  done

  cd "$project_dir"
}

cd "$root/$project" || exit

  case $project in
    game)
      generate_folder_schemas "$(pwd)/schemas" "$(pwd)/data/main/UI/src/generated" ts;
      generate_folder_schemas "$(pwd)/schemas" "$(pwd)/app/include/game/generated" cpp;
      ;;
    editor)
      generate_folder_schemas "$(pwd)/schemas" "$(pwd)/data/main/UI/src/generated" ts;
      generate_folder_schemas "$(pwd)/schemas" "$(pwd)/app/include/editor/generated" cpp;
      ;;
    *) echo "Unknown project: $project"; exit 1 ;;
  esac

cd "$call_dir" || exit
