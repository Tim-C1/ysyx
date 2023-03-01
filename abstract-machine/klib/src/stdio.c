#include <am.h>
#include <klib-macros.h>
#include <klib.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
static void strrev(char *str);

int itoa(long long num, char *str, int base);

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
  long long d;
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
        d = va_arg(ap, long long);
        tmp = tmp + itoa(d, tmp, 10);
        break;
      case 'p':
        d = va_arg(ap, long long);
        tmp = tmp + itoa(d, tmp, 16);
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
  va_list ap;
  va_start(ap, fmt);
  int nw = vsnprintf(out, n, fmt, ap);
  va_end(ap);
  return nw;
}


int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  int nw = vsprintf(out, fmt, ap);
  if (nw >= n) {
      out[n-1] = '\0';
      return n;
  }
  return nw;
}

/* decimal number to string */
int itoa(long long num, char *str, int base) {
  char sign = '+';
  int cnt = 0;
  int digit;
  if (num < 0) {
    num = -num;
    sign = '-';
  }
  if (base == 10) {
      do {
        digit = num % 10;
        *(str + cnt) = (char)('0' + digit);
        num /= 10;
        cnt++;
      } while (num != 0);
  } else {
      do {
          digit = num % 16;
          if (digit < 10) {
              *(str + cnt) = (char)('0' + digit);
              num /= 16;
              cnt++;
          } else {
              *(str + cnt) = (char)('a' + digit - 10);
              num /= 16;
              cnt++;
          }
       } while (num != 0);
  }
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
