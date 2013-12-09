/* 
 * A simple unit test for make_keyimg.c and extract_keyimg.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <stdbool.h>

#include "toxkeyimg.h"

static void random_key(char *s)
{
    int i;

    for (i = 0; i < KEYLEN; ++i)
        snprintf(s+i, sizeof(s), "%x", rand() % 16);
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3) {
        printf("Usage: [num tests] (-m to mute)\n");
        return -1;
    }

    bool mute = false;

    if (argc == 3 && strcmp(argv[2], "-m") == 0)
        mute = true;

    int n = atoi(argv[1]);
    int i;

    for (i = 0; i < n; ++i) {
        if (!mute)
            printf("* Test %d\n", i+1);

        const char *outpath = "testkeyimg.tox";

        /* Generate new key image */
        char key_in[BUF_SIZE] = {'\0'};
        random_key(key_in);

        assert (make_keyimg(key_in, outpath) == 0);

        /* Extract key from generated image */
        char key_out[BUF_SIZE] = {'\0'};

        assert (extract_keyimg(key_out, outpath) == 0);

        /* Compare to original key */
        if (!mute) {
            printf("IN :%s\n", key_in);
            printf("OUT:%s\n\n", key_out);
        }

        assert (strcmp(key_in, key_out) == 0);
    }

    printf("Tests passed!\n");
    return 0;
}
