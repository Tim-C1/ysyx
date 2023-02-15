#include <isa.h>
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"
#include <memory/vaddr.h>
static int is_batch_mode = false;

void init_regex();
void init_wp_pool();
int new_wp(char *exp);
char* get_exp(int NO);
void free_wp_no(int NO);
void display_all(void);

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

/*  if (line_read) {
    free(line_read);
    line_read = NULL;
  }
*/
  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
    if (!(nemu_state.state == NEMU_ABORT || nemu_state.halt_ret !=0)) {
      nemu_state.state = NEMU_QUIT;  
    }
    return -1;
}

static int cmd_help(char *args);
static int cmd_si(char *args);
static int cmd_info(char *args);
static int cmd_scan_mem(char *args);
static int cmd_p(char *args);
static int cmd_w(char *args);
static int cmd_d(char *args);

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display informations about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },

  /* TODO: Add more commands */
  { "si", "Execute the program step by step", cmd_si },
  { "info", "show information about (r register ...)", cmd_info },
  { "x", "scan memory nearby", cmd_scan_mem },
  { "p", "calculate the value of a expression", cmd_p},
  { "w", "set a watchpoint to a expression", cmd_w},
  { "d", "delete a watchpoint", cmd_d},
  
};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) { /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

/* implement the step function */
static int cmd_si(char *args){
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  /* convert the string into uint64_t */
  char *left = NULL;
  uint64_t step = strtoul(arg, &left, 10);
  cpu_exec(step); 
  return 0;
}

/* implement the info function */
static int cmd_info(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  if (arg == NULL) {
    return -1;
  /* info r command to print the register */
  } else if (strcmp(arg, "r") == 0) {
      isa_reg_display();
      return 0;
  } else if (strcmp(arg, "w") == 0) {
      // display_all();
      return 0;
  }
  return -1;
}

/* implement function for scanning the memory*/
static int cmd_scan_mem(char *args) {
  /* extract the arguments */
  char *arg1 = strtok(NULL, " ");
  char *arg2 = strtok(NULL, " ");

  uint64_t op1, op2;
  bool success = 0;
  sscanf(arg1, "%lu", &op1);
  op2 = expr(arg2, &success);
  if (success) {
  }
  /* sscanf(arg2, "%lx", &op2); */

  vaddr_t addr = op2;
  
  /* print 4 byte one time */
  int i = 0;
  while (i < op1*4) {
    word_t val = vaddr_read(addr + i, 4);
    printf("%#016lx\t%#016lx\n", addr + i, val);
    i = i + 4; 
  }
  return 0;
}

/* implement the function for expression */
static int cmd_p(char *args) {
    char *exp = strtok(NULL, " ");
    bool success = true;
    uint64_t rst = expr(exp, &success);
    if (success) {
        printf("the result is %lu \n", rst);
        return 0;
    }
    printf("expr failed, pls check your expression ! \n");
    return -1;
}

/* implement the function for setting a watchpoint */
static int cmd_w(char *args) {
    char *exp = strtok(NULL, " ");
    int NO = new_wp(exp);
    printf("a new watchpoint is set, the number is %d, the expression is %s\n", NO, get_exp(NO));
    return 0;
}
    
static int cmd_d(char *args) {
    int NO = atoi(strtok(NULL, " "));
    free_wp_no(NO);
    return 0;
}


void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
