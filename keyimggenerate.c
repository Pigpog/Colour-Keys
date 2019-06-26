/* 
 * Generates key images.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>

#include "toxkeyimg.h"

void stringLwr(char *s){
    int len,i;
    len=strlen(s);
     
    for(i=0;i<len;i++)
        s[i]=tolower(s[i]);
}

int main(int argc, char *argv[])
{
    if (argc > 3 || argc==1) {
        printf("Usage: [Tox ID] [Path]\n");
        return -1;
    }
    const char *outpath = argv[2];
    stringLwr(argv[1]);
    const char *key_in = argv[1];

    /* Generate new key image */
    assert (make_keyimg(key_in, outpath) == 0);

    /* Validate generated image */
    char key_out[BUF_SIZE] = {'\0'};

    assert (extract_keyimg(key_out, outpath) == 0);

    /* Compare to original key */
    printf("IN :%s\n", key_in);
    printf("OUT:%s\n\n", key_out);

    assert (strcmp(key_in, key_out) == 0);

    printf("Output passed validation.\n");
    return 0;
}
