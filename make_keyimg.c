/* 
 * Creates a colour-encoded tox key-image using the digits 
 * from a tox public key/KEY.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "toxkeyimg.h"
#include "bitmap.h"

/* Default path to template key */
#define INNAME "keytemplate.tox"

int make_keyimg(const char *key, const char *outpath) 
{
    FILE *fpin = fopen(INNAME, "r");

    if (fpin == NULL) {
        printf("Template image not found\n");
        return -1;
    }

    FILE *fpout = fopen(outpath, "w");

    if (fpout == NULL) {
        printf("Error opening write file. Exiting.\n");
        fclose(fpin);
        return -2;
    }

    if (strlen(key) != KEYLEN) {
        fclose(fpin);
        fclose(fpout);
        printf("Incorrect key length\n");
        return -3;
    }

    /* Read template header info */
    BITMAPFILEHEADER bfh;
    fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpin);

    BITMAPINFOHEADER bih;
    fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpin);

    /* Make sure fpin is correct file format */
    if (bfh.signature != 0x4d42 || bfh.toxcode != TOXCODE 
                    || bfh.offset != 54 || bih.headersize != 40 
                    || bih.bit_count != 24 || bih.compression != 0) {
        fclose(fpin);
        fclose(fpout);
        printf("Invalid file format.\n");
        return -4;
    }

    int rgbsize = sizeof(RGB);
    int old_width = bih.width;
    int old_padding = (4 - (bih.width * rgbsize) % 4) % 4;

    /* Calculate new size and write new header to fpout */
    bih.width *= IMGSIZE;
    bih.height *= IMGSIZE;
    int new_padding = (4 - (bih.width * rgbsize) % 4) % 4;
    bih.imgsize = (bih.width * bih.height) + (bih.height * new_padding);    
    bfh.filesize = bih.imgsize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fpout);
    fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fpout);

    int i, j;
    int dgt_i = 0;
    for (i = 0; i < bih.height; ++i) {
        int dgt_i_strt = dgt_i;

        for (j = 0; j < bih.width; ++j) {
            bool f_pxlclr = false;
            RGB rgb;
            fread(&rgb, rgbsize, 1, fpin);

            /* Convert image (non-background) pixels to respective key values */
            if (rgb.blue == DFLTCLR && rgb.green == DFLTCLR && rgb.red == DFLTCLR) {
                f_pxlclr = true;
                char buf[3];
                char btmp0 = key[dgt_i++ % KEYLEN];
                char btmp1 = key[dgt_i++ % KEYLEN];
                snprintf(buf, sizeof(buf), "%c%c", btmp0, btmp1);
                rgb.blue = strtol(buf, NULL, 16);

                char gtmp0 = key[dgt_i++ % KEYLEN];
                char gtmp1 = key[dgt_i++ % KEYLEN];
                snprintf(buf, sizeof(buf), "%c%c", gtmp0, gtmp1);
                rgb.green = strtol(buf, NULL, 16);

                char rtmp0 = key[dgt_i++ % KEYLEN];
                char rtmp1 = key[dgt_i++ % KEYLEN];
                snprintf(buf, sizeof(buf), "%c%c", rtmp0, rtmp1);
                rgb.red = strtol(buf, NULL, 16);
            }

            fwrite(&rgb, rgbsize, 1, fpout);

            /* Scale pixel horizontally */
            if ( ((j+1) % IMGSIZE) != 0 ) {
                fseek(fpin, -rgbsize, SEEK_CUR);
                if (f_pxlclr)
                    dgt_i -= SIZE_RGB;
            }
        }

        int k;

        for (k = 0; k < new_padding; ++k)
            fputc(0x00, fpout);

        /* Scale pixel vertically */
        if ( ((i + 1) % IMGSIZE) != 0 ) {
            fseek(fpin, -old_width * rgbsize, SEEK_CUR);
            dgt_i = dgt_i_strt;
        } else {
            fseek(fpin, old_padding, SEEK_CUR);
        }
    }

    fclose(fpin);
    fclose(fpout);
    return 0;
}
