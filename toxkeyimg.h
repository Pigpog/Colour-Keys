/* number of chars in a tox public key */
#define KEYLEN     76

/* Buffers need extra room for remainder bytes on last write */
#define BUF_SIZE 80

/* factor by which the key image is enlarged from the template */
#define IMGSIZE   5

/* Default colour of "storage" pixels for template (i.e. not background) */
#define DFLTCLR   0x00

/* Image background colour */
#define BKRNDCLR  0xFF

/* Tox key-image signature */
#define TOXCODE   0x7854

/* size of RGB sequence */
#define SIZE_RGB 6

int make_keyimg(const char *KEY, const char *outpath);
int extract_keyimg(char *KEY, const char *path);
