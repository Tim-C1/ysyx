#include <common.h>
#include <memory.h>

void init_disasm(const char *triple);
extern void init_ftrace(const char *elf_file);
extern void init_difftest(char *ref_so_file, long img_size, int port);
extern void init_device();
static int difftest_port = 1234;

static long load_img(char *img_path){
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
    return size;
}

void init_npc_monitor(char *img, char *elf_file, char *ref_so_file) {
    /* load the binary program */
    long img_size = load_img(img);

    /* init ftrace */
    init_ftrace(elf_file);

    /* init llvm disassembler */
    init_disasm("riscv64-pc-linux-gnu");

    /* init difftest */
    init_difftest(ref_so_file, img_size, difftest_port);

    init_device();
}
