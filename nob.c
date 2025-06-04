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