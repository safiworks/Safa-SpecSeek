#!/bin/bash

REPO_URL="https://github.com/Mellurboo/SpecSeek.git"
TARGET_DIR="user/specseek"
NOB_PROJECTS="user/nob.c"

mkdir -p "$TARGET_DIR"
git clone "$REPO_URL" "$TARGET_DIR"

if [ $? -eq 0 ]; then
    echo "specseek has cloned into $TARGET_DIR"
else
    echo "Failed to clone repository? check it's still there"
    exit 1
fi

if grep -q "\"specseek\"" "$NOB_PROJECTS"; then
    echo "specseek was already in user/nob.c projects array?"
else
    sed -i "/projects\[\].*{/,/};/ s/};/    \"specseek\",\n};/" "$NOB_PROJECTS"
    echo "added specseek to user/nob.c projects array"
fi

    echo "Writing nob.c to $TARGET_DIR/nob.c"
    cat > "$TARGET_DIR/nob.c" <<'EOF'
#define NOB_STRIP_PREFIX
#define NOB_IMPLEMENTATION
#include "../nob.h"

int main(int argc, char** argv) {
    NOB_GO_REBUILD_URSELF(argc, argv); // <- That way nob automatically rebuilds itself when changed.
    Cmd cmd = { 0 };
    cmd_append(&cmd, "make");
    if(!cmd_run_sync_and_reset(&cmd)) return 1;
    char* minos_root = getenv("MINOSROOT");
    if(!minos_root) {
        nob_log(NOB_ERROR, "Missing $MINOSROOT");
        return 1;
    }
    if(!copy_file("bin/minos/64/specseek_minos_64", temp_sprintf("%s/initrd/user/specseek", minos_root))) return 1;
}
EOF

    # Confirm the file was written
    if [ -f "$TARGET_DIR/nob.c" ]; then
        ls -l "$TARGET_DIR/nob.c"
    else
        echo "Failed to generate nob.c"
    fi
