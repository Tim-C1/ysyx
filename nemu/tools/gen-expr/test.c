#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char *str = "2 +3+   (23-22)\n8  - 2+ 9*(  2-7)  ";
    
    printf("og: %s\n", str);
    char *si = strtok(str,"\n");
    char *sj = strtok(NULL,"\n");

    printf("si = %s\n sj = %s\n", si, sj);

    return 0;
    
}


