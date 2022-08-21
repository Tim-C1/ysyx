#include <common.h>

void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();
word_t expr(char *e, bool *success);
static void read_input(char *input[]);
static int compare_exp(void);

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif
  
  compare_exp();
  /* Start engine. */
  engine_start();
return is_exit_status_bad();
}

static void read_input(char *input[]) {
    int cnt = 0;
    char lines[99999];
    FILE *fp = fopen("/home/ctr/ysyx-workbench/nemu/tools/gen-expr/input", "r");
    int n = fread(lines, 99999, 1, fp);
    if (n)
        ;
    printf("printing the content of input test:\n");
    printf("%s", lines);
    fclose(fp);
    input[cnt] = strtok(lines, "\n");
    printf("line %d : %s\n", cnt+1, input[cnt]); 
    while ( (input[++cnt] = strtok(NULL, "\n")) != NULL ) {
        printf("line %d : %s\n", cnt+1, input[cnt]); 
    }
}

static int compare_exp(void) {
    char *input[99999];
    bool *success = 0;

    read_input(input);
    int i = 0;
    while (input[i] != NULL) {
        uint64_t rst;
        sscanf(strtok(input[i], "@"), "%lu", &rst);
        char *exp = strtok(NULL, "@");
        uint64_t my_rst = expr(exp, success);
        if (my_rst != rst) {
            printf("wrong at line: %d, expression: %s, expected: %lu, but get: %lu\n", i+1, exp, rst, my_rst);
        } else {
            printf ("success at line: %d, expression %s\n", i+1, exp);
        }
        i++;
    }
    return 1;
}

