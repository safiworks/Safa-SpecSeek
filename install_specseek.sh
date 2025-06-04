#!/bin/bash

REPO_URL="https://github.com/Mellurboo/SpecSeek.git"
TARGET_DIR="user/specseek"
NOB_PROJECTS="user/nob.c"

mkdir -p "$TARGET_DIR"
git clone --branch MinOS-Port "$REPO_URL" "$TARGET_DIR"

if [ $? -eq 0 ]; then
    echo "specseek has cloned into $TARGET_DIR"
else
    echo "Failed to clone repository? check it's still there"
    exit 1
fi

if grep -q "\"specseek\"" "$NOB_PROJECTS"; then
    echo "specseek was already in user/nob.c projects array?"
    exit 0
else
    sed -i "/projects\[\].*{/,/};/ s/};/    \"specseek\",\n};/" "$NOB_PROJECTS"
    echo "added specseek to user/nob.c projects array"
fi
