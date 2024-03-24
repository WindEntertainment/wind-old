# SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# echo "${SCRIPT_DIR}"

# # Run clang-format on all C++ and C source files in the project directory
# find "$SCRIPT_DIR" \( -name '*.cpp' -o -name '*.h' \) -exec echo {} \;
# # clang-format -i {}

#!/bin/bash

# Get the absolute path to the directory containing this script
# SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# # Set the absolute path to your project's source files
# PROJECT_DIR="$SCRIPT_DIR"

# # Parse the .gitignore file to extract folder names
# IGNORE_FOLDERS=()
# while IFS= read -r line; do
#     if [[ "$line" =~ ^/?(.*)/ ]]; then
#         IGNORE_FOLDERS+=("${BASH_REMATCH[1]}")
#     fi
# done < "$PROJECT_DIR/.gitignore"

# # Build the find command with exclusions
# FIND_COMMAND="find "$SCRIPT_DIR" \( -name '*.cpp' -o -name '*.h' \)"
# for folder in "${IGNORE_FOLDERS[@]}"; do
#     FIND_COMMAND+=" -not -path \"*/$folder/*\""
# done

# echo "${FIND_COMMAND}"

# FIND_COMMAND+=" -exec clang-format -i {} \;"
# echo "$FIND_COMMAND"

# find "$SCRIPT_DIR"

# Run clang-format on all C++ and C source files in the project directory
# eval "$FIND_COMMAND"


#!/bin/bash


# Get the absolute path to the directory containing this script
# SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[1]}" )" &> /dev/null && pwd )"

# # Set the absolute path to your project's source files
# PROJECT_DIR="$SCRIPT_DIR"

# # Parse the .gitignore file to extract folder and file patterns
# IGNORE_PATTERNS=()
# while IFS= read -r line; do
#     # Ignore comments and blank lines
#     if [[ "$line" =~ ^[^#]*$ ]]; then
#         IGNORE_PATTERNS+=("$line")
#     fi
# done < "$PROJECT_DIR/.gitignore"

# # Build the find command with exclusions
# FIND_COMMAND="find \"$PROJECT_DIR\" \( -name '*.cpp' -o -name '*.h' \)"
# for pattern in "${IGNORE_PATTERNS[@]}"; do
#     FIND_COMMAND+=" -not -path \"*$pattern*\""
# done
# FIND_COMMAND+=" -exec echo \"Formatting file: {}\" \; -exec clang-format -i {} \;"

# # echo "$FIND_COMMAND"
# # Run clang-format on all C++ and C source files in the project directory
# # echo "$FIND_COMMAND"
# eval "$FIND_COMMAND"

# PROJECT_DIR="${PROJECT_DIR:-$(pwd)}"

# # Parse the .gitignore file in the project directory to extract folder and file patterns
# IGNORE_PATTERNS=()
# if [[ -f "$PROJECT_DIR/.gitignore" ]]; then
#     while IFS= read -r line; do
#         # Ignore comments and blank lines

#         if [[ "$line" =~ ^[^#]*$ ]]; then
#             IGNORE_PATTERNS+=("$line")
#         fi
#     done < "$PROJECT_DIR/.gitignore"
# fi

# # Build the find command with exclusions and echoing found files
# FIND_COMMAND="find \"$PROJECT_DIR\" \( -name '*.cpp' -o -name '*.h' \)"
# for pattern in "${IGNORE_PATTERNS[@]}"; do
#     FIND_COMMAND+=" -not -path \"$pattern\""
# done
# FIND_COMMAND+=" -exec echo \"Formatting file: {}\" \; -exec clang-format -i {} \;"

# # Run clang-format on all C++ and C source files in the project directory
# echo "$FIND_COMMAND"
# eval "$FIND_COMMAND"

#!/bin/bash

# Set the project directory to the value of the PROJECT_DIR environment variable
PROJECT_DIR="${PROJECT_DIR:-$(pwd)}"

# Parse the .gitignore file in the project directory to extract folder and file patterns
IGNORE_PATTERNS=()
if [[ -f "$PROJECT_DIR/.gitignore" ]]; then
    while IFS= read -r pattern; do
        # Ignore comments and blank lines
        if [[ "$pattern" != \#* && ! -z "$pattern" ]]; then
            IGNORE_PATTERNS+=("-not" "-path" "$PROJECT_DIR/$pattern" "-prune")
        fi
    done < "$PROJECT_DIR/.gitignore"
fi

# Build the find command with exclusions and echoing found files
FIND_COMMAND="find \"$PROJECT_DIR\" \( -name '*.cpp' -o -name '*.h' \)"
for exclude in "${IGNORE_PATTERNS[@]}"; do
    FIND_COMMAND+=" $exclude"
done
FIND_COMMAND+=" -type f -exec echo \"Formatting file: {}\" \; -exec clang-format -i {} \;"

# Run clang-format on all C++ and C source files in the project directory
echo "$FIND_COMMAND"
eval "$FIND_COMMAND"
