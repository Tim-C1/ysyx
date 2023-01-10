#include <common.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <cpu.h>

extern void scan_mem(char *args);
extern uint64_t *cpu_gpr;

static int cmd_c(char *args);
static int cmd_si(char *args);
static int cmd_q(char *args);
static int cmd_info(char *args);
static int cmd_scan_mem(char *args);

void exec(uint32_t num);
static char* rl_gets() {
  static char *line_read = NULL;
  line_read = readline("(npc) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NPC", cmd_q },
  { "si", "Execute the program step by step", cmd_si },
  { "info", "show information about (r register ...)", cmd_info },
  { "x", "scan memory nearby", cmd_scan_mem },
};

#define NR_CMD (int)(sizeof(cmd_table) / sizeof(cmd_table[0]))


static int cmd_c(char *args) {
    exec(-1);
    return 0;
}

static int cmd_q(char *args) {return -1;}

static int cmd_si(char *args) {
    exec(1);
    return 0;
}

static int cmd_info(char *args) {
  int i;
  assert(cpu_gpr);
  for (i = 0; i < 32; i++) {
    printf("gpr[%d] = 0x%lx\n", i, cpu_gpr[i]);
  }
  return 0;
}

static int cmd_scan_mem(char *args) {
    scan_mem(args);
    return 0;
} 

void npc_sdb_mainloop(void) {
  for (char *str; (str = rl_gets()) != NULL;) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) {
      continue;
    }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

    int i;
    for (i = 0; i < NR_CMD; i++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) {
          return;
        }
        break;
      }
    }

    if (i == NR_CMD) {
      printf("Unknown command '%s'\n", cmd);
    }
  }
}
