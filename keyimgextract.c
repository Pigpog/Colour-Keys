/* 
 * Extracts keys from images.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "toxkeyimg.h"

int main(int argc, char *argv[])
{
    if (argc > 2 || argc==1) {
        printf("Usage: [Path]\n");
        return -1;
    }

    char key_out[BUF_SIZE] = {'\0'};
    assert (extract_keyimg(key_out, argv[1]) == 0);
    printf("KEY:%s\n\n", key_out);
    return 0;
}
