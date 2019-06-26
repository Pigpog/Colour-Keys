/* 
 * Extracts keys from images.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <stdbool.h>

#include "toxkeyimg.h"

int main(int argc, char *argv[])
{
    if (argc > 2 || argc==1) {
        printf("Usage: [Path]\n");
        return -1;
    }
    const char *path = argv[1];

    /* Validate generated image */
    char key_out[BUF_SIZE] = {'\0'};

    assert (extract_keyimg(key_out, path) == 0);

    printf("KEY:%s\n\n", key_out);
    return 0;
}
