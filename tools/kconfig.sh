#!/bin/bash

CONFIG_FILE=".config"
HEADER_FILE="kernel/src/gen/autoconf.h"

echo "/* Auto-generated header */" > "$HEADER_FILE"

while IFS= read -r line; do
    [[ "$line" =~ ^#.*$ || -z "$line" ]] && continue
    if [[ "$line" =~ ^CONFIG_([A-Z0-9_]+)=(.*)$ ]]; then
        name="${BASH_REMATCH[1]}"
        value="${BASH_REMATCH[2]}"
        value="${value%\"}"
        value="${value#\"}"
        macro_name="${name#ENABLE_}"
        echo "#define $macro_name $value" >> "$HEADER_FILE"
    fi
done < "$CONFIG_FILE"

echo "Header generated in $HEADER_FILE"
