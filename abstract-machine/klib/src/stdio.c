#include <am.h>
#include <klib-macros.h>
#include <klib.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
static void strrev(char *str);

int itoa(int num, char *str);

int printf(const char *fmt, ...) {
  char buf[10000];
  va_list ap;
  va_start(ap, fmt);
  int n = vsprintf(buf, fmt, ap);
  va_end(ap);
  putstr(buf);
  return n;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  int cnt = 0;
  char *s;
  int d;
  char *tmp = out;
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

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int n = vsprintf(out, fmt, ap);
  va_end(ap);
  return n;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}


int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  int cnt = 0;
  char *s;
  int d;
  char *tmp = out;
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
#endif
