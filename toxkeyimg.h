/* number of chars in a tox public key */
#define KEYLEN     76

/* factor by which the key image is enlarged from the template */
#define IMGSIZE   5

/* Default colour of "storage" pixels for template (i.e. not background) */
#define DFLTCLR   0x00

/* Image background colour */
#define BKRNDCLR  0xFF

/* Tox key-image signature */
#define TOXCODE   0x7854

int make_keyimg(char KEY[], const char *outpath);
char *extract_keyimg(char KEY[], const char *path);