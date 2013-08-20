/*
 * Extracts a 38 byte tox public key/KEY from an encoded tox key-image
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "toxkeyimg.h"
#include "bitmap.h"

char *extract_keyimg(char KEY[], const char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp) {
        printf("File not found\n");;
        return NULL;
    }

    BITMAPFILEHEADER bfh;
    fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fp);

    BITMAPINFOHEADER bih;
    fread(&bih, sizeof(BITMAPINFOHEADER), 1, fp);

    if (bfh.signature != 0x4d42 || bfh.toxcode != TOXCODE 
                    || bfh.offset != 54 || bih.headersize != 40 
                    || bih.bit_count != 24 || bih.compression != 0) {
        fclose(fp);
        printf("Invalid file format.\n");
        return NULL;
    }

    int rgbsize = sizeof(RGB);
    int padding = (4 - (bih.width * rgbsize) % 4) % 4;
    int newcol = 0;
    int newrow = 0;
    int i, j;

    for (i = 0; i < bih.height; ++i) {
        for (j = 0; j < bih.width; ++j) {
            RGB rgb;
            fread(&rgb, rgbsize, 1, fp);

            /* Take only the first pixel's value from each coloured-section */
            if (newrow == 0 && (newcol++ % IMGSIZE) == 0
                            && !(rgb.blue == BKRNDCLR 
                            &&   rgb.green == BKRNDCLR 
                            &&   rgb.red == BKRNDCLR)) {
                char buf[7];
                snprintf(buf, sizeof(buf), "%02x%02x%02x", rgb.blue, rgb.green, rgb.red);
                strncat(KEY, buf, sizeof(buf)-1);

                /* Return after the first KEYLEN digits */
                if (strlen(KEY) >= KEYLEN) {
                    KEY[KEYLEN] = '\0';
                    fclose(fp);
                    return KEY;
                }
            }
        }
        newrow = (newrow+1) % IMGSIZE;
        fseek(fp, padding, SEEK_CUR);
    }
    fclose(fp);
    printf("Something went wrong\n");
    return NULL;
}

