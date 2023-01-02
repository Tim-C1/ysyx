#include <common.h>
#include <elf.h>
#include <stdio.h>

static Elf64_Ehdr ehdr;
static Elf64_Shdr shdrs[1024];
static char shstrtab[1024];
static char strtab[1024];
static Elf64_Sym symtab[1024];
static int symtab_num;

static bool elf_check_file(Elf64_Ehdr *hdr) {
    if(!hdr) return false;
    if(hdr->e_ident[EI_MAG0] != ELFMAG0) {
        printf("ELF Header EI_MAG0 incorrect.\n");
        return false;
    }
    if(hdr->e_ident[EI_MAG1] != ELFMAG1) {
        printf("ELF Header EI_MAG1 incorrect.\n");
        return false;
    }
    if(hdr->e_ident[EI_MAG2] != ELFMAG2) {
        printf("ELF Header EI_MAG2 incorrect.\n");
        return false;
    }
    if(hdr->e_ident[EI_MAG3] != ELFMAG3) {
        printf("ELF Header EI_MAG3 incorrect.\n");
        return false;
    }
    return true;
}

char *get_func_symbol_by_address(uint64_t addr, int type) {
    char *func_name = NULL;
    for (int i = 0; i < symtab_num; i++) {
        Elf64_Sym symbol = symtab[i];
        if (type == 1) {
            if (symbol.st_value == addr && ELF64_ST_TYPE(symbol.st_info) == STT_FUNC) {
                func_name = &strtab[symbol.st_name];
            }
        } else {
            if ((addr >= symbol.st_value && addr <= symbol.st_value + symbol.st_size) && ELF64_ST_TYPE(symbol.st_info) == STT_FUNC) {
                func_name = &strtab[symbol.st_name];
            }
        }
    } 
    return func_name;
}

void init_ftrace(const char *elf_file) {
    FILE *fp = fopen(elf_file, "rb");
    if (fp == NULL) {
      printf("Unable to open '%s'\n", elf_file);
      return;
    }

    if (fread(&ehdr, sizeof(ehdr), 1, fp) != 1) {
      printf("fread: can not read elf header \n");
      fclose(fp);
      return;
    }

    if (!elf_check_file(&ehdr)) {
      printf("'%s' is not an ELF file\n", elf_file);
      fclose(fp);
      return;
    }

    /* get section headers */
    fseek(fp, ehdr.e_shoff, SEEK_SET);
    if(fread(&shdrs, ehdr.e_shentsize, ehdr.e_shnum, fp) != ehdr.e_shnum) {
        printf("fread: can not read shdrs\n");
    }
    rewind(fp);

    /* get shstrtab */
    Elf64_Shdr strtabsh = shdrs[ehdr.e_shstrndx];
    fseek(fp, strtabsh.sh_offset, SEEK_SET);
    if(fread(&shstrtab, 1, strtabsh.sh_size, fp) != strtabsh.sh_size) {
        printf("fread: can not read shstrtab\n");
    }
    rewind(fp); 
    
    /* get strtab and symtab */
    for (int i = 0; i < ehdr.e_shnum; i++) {
        Elf64_Shdr shdr = shdrs[i];
        char *shname = &shstrtab[shdr.sh_name];
        if (strcmp(shname, ".strtab") == 0) {
            fseek(fp, shdr.sh_offset, SEEK_SET);
            if(fread(&strtab, 1, shdr.sh_size, fp) != shdr.sh_size) {
                printf("fread: can not read strtab\n");
            }
            rewind(fp);
        }
        if (strcmp(shname, ".symtab") == 0) {
            fseek(fp, shdr.sh_offset, SEEK_SET);
            if(fread(&symtab, shdr.sh_entsize, shdr.sh_size / shdr.sh_entsize, fp) != shdr.sh_size / shdr.sh_entsize) {
                printf("fread: can not read symtab\n");
            }
            rewind(fp);
            symtab_num = shdr.sh_size / shdr.sh_entsize;
        }
    }
}

