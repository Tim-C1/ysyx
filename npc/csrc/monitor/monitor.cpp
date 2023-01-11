#include <common.h>
#include <memory.h>

void init_disasm(const char *triple);
static void load_img(char *img_path){
    if (img_path == NULL) {
        printf("no img is given\n");
        assert(0);
    }
    FILE *fp = fopen(img_path, "rb");
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    fseek(fp, 0 , SEEK_SET);
    int ret = fread(guest_to_host(RESET_VECTOR), size, 1, fp);
    assert(ret == 1);

    fclose(fp);
}

void init_npc_monitor(char *img) {
    /* load the binary program */
    load_img(img);

    /* init llvm disassembler */
    init_disasm("riscv64-pc-linux-gnu");
}
