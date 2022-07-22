#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned long int result = %s; "
"  printf(\"%%lu\", result); "
"  return 0; "
"}";

static uint32_t choose(uint32_t n) {
    return rand() % n;
}

static int str_len = 0;
static void gen_rand_expr() {
  switch (choose(3)) {
      case 0:
          buf[str_len++] = choose(9)+1+'0';
          break;
      case 1:
          if (choose(4) == 1) {
              buf[str_len++] = ' ';
          }
          buf[str_len++] = '(';
          gen_rand_expr();
          buf[str_len++] = ')';
          break;
      default:
          if (choose(4) == 1) {
              buf[str_len++] = ' ';
          }
          gen_rand_expr();
          if (choose(4) == 1) {
              buf[str_len++] = ' ';
          }
          int status = choose(4);
          switch (status) {
              case 0:
                  buf[str_len++] = '+';
                  break;
              case 1:
                  buf[str_len++] = '-';
                  break;
              case 2:
                  buf[str_len++] = '*';
                  break;
              case 3:
                  buf[str_len++] = '/';
                  break;
          }
          gen_rand_expr();
    }
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    memset(buf, 0, sizeof buf);
    str_len = 0;
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc -O2 -Wall -Werror /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    unsigned long int result;
    if (fscanf(fp, "%lu", &result));
    pclose(fp);

    printf("%lu@%s\n", result, buf);
  }
  return 0;
}
