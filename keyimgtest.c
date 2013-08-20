/* 
 * A simple unit test for make_keyimg.c and extract_keyimg.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include "toxkeyimg.h"

static char *random_key(char s[])
{
    int i;
    for (i = 0; i < KEYLEN; ++i)
        snprintf(s+i, sizeof(s), "%x", rand() % 16);
    return s;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: [n] tests\n");
        return 1;
    }

    int n = atoi(argv[1]);
    int i;
    for (i = 0; i < n; ++i) {
        printf("* Test %d\n", i+1);
        const char *outpath = "testkeyimg.tox";

        /* Generate new key image */
        char key_in[KEYLEN-2] = {'\0'};
        random_key(key_in);
        assert (make_keyimg(key_in, outpath) == 0);

        /* Extract key from generated image */
        char key_out[KEYLEN-2] = {'\0'};
        extract_keyimg(key_out, outpath);

        /* Compare to original key */
        printf("IN :%s\n", key_in);
        printf("OUT:%s\n\n", key_out);
        assert (strcmp(key_in, key_out) == 0);
    }

    printf("Tests passed!\n");
    return 0;
}
