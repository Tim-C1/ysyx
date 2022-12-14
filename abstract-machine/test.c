#include <stdarg.h>
#include <assert.h>
#include <string.h>
static void strrev(char *str);

int itoa(int num, char *str);

int sprintf(char *out, const char *fmt, ...) {
  int cnt = 0;
  va_list ap;
  char *s;
  int d;
  char *tmp = out;
  va_start(ap, fmt);
  while (*fmt) {
    if (*fmt == '%') {
      // must have a specifier
      fmt++;
      switch (*fmt) {
      case 's':
        s = va_arg(ap, char *);
        strcpy(tmp, s);
        tmp = tmp + strlen(s);
        break;
      case 'd':
        d = va_arg(ap, int);
        tmp = tmp + itoa(d, tmp);
        break;
      }
      fmt++;
    } else {
      *tmp++ = *fmt++;
    }
  }
  *tmp = '\0';
  cnt = strlen(out);
  return cnt;
}

/* decimal number to string */
int itoa(int num, char *str) {
  char sign = '+';
  int cnt = 0;
  int digit;
  if (num < 0) {
    num = -num;
    sign = '-';
  }
  do {
    digit = num % 10;
    *(str + cnt) = (char)('0' + digit);
    num /= 10;
    cnt++;
  } while (num != 0);
  if (sign == '-') {
    *(str + cnt) = sign;
    cnt++;
  }
  *(str + cnt) = '\0';
  strrev(str);
  return cnt;
}

/* reverse a string */
static void strrev(char *str) {
  int i;
  int j;
  char a;
  int len = strlen(str);
  for (i = 0, j = len - 1; i < j; i++, j--) {
    a = str[i];
    str[i] = str[j];
    str[j] = a;
  }
}

int main() {
    char buf[120];
    sprintf(buf, "%s\n", "hello, world!");
    assert(strcmp(buf, "hello, world!\n") == 0);
    sprintf(buf, "%d + %d = %d\n", 1, 1, 2);
    assert(strcmp(buf, "1 + 1 = 2\n") == 0);
    
    return 0;
}
