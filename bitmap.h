/*
*   Bitmap file structure data. 
*/

#include <stdint.h>

typedef struct 
{
    uint16_t signature;
    uint32_t filesize;
    uint16_t toxcode;    /* Signature for tox key-images. Set to 0x7854 */
    uint16_t reserved2;
    uint32_t offset;
} __attribute__((__packed__)) BITMAPFILEHEADER;
       
typedef struct
{
    uint32_t headersize;
    int32_t  width;
    int32_t  height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t imgsize;
    int32_t  x_pxls_pm;
    int32_t  y_pxls_pm;
    uint32_t num_clrs;
    uint32_t num_imp_clrs;
} __attribute__((__packed__)) BITMAPINFOHEADER;

typedef struct
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} __attribute__((__packed__)) RGB;
