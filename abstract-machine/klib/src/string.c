#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
    size_t cnt = 0;
    while(*s != '\0') {
        s++;
        cnt++;
    }
    return cnt;
}

char *strcpy(char *dst, const char *src) {
    size_t i;
    size_t src_len = strlen(src);
    for (i = 0; i < src_len; i++) {
        *(dst+i) = *(src+i);
    }
    dst[i] = '\0';
    return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
    size_t i;
    size_t dis_len = strlen(dst);
    for (i = 0; src[i] != '\0'; i++) {
        dst[dis_len + i] = src[i];
    }
    dst[dis_len + i] = '\0';
    return dst;
}

int strcmp(const char *s1, const char *s2) {
    while(*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  panic("Not implemented");
}

void *memset(void *s, int c, size_t n) {
    size_t i;
    unsigned char *p = (unsigned char *) s;
    for (i = 0; i < n; i++) {
        *p++ = (unsigned char) c;
    }
    return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
    size_t i = 0;
    char *p = (char *) out;
    const char *p_in = (const char *) in;
    while(i < n) {
        *p++ = *p_in++;
        i++;
    }
    return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    unsigned char *p1 = (unsigned char *) s1;
    unsigned char *p2 = (unsigned char *) s2;

    while (n > 0) {
        if (*p1 != *p2) {
            return *p1 - *p2;
        }
        n--;
        p1++;
        p2++;
    }
    return 0;
}

#endif
