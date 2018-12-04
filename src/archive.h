#ifndef __KANSAI_ARCHIVE
#define __KANSAI__ARCHIVE

/* archive file offsets */
#define HEADER_SIZE 10
#define FILE_OFFSET 4
#define ARCHIVE_PADDING 10
#define HASH_SIZE 16

#include <stdint.h>
/* associative table entry */
struct asset_t {
    uint8_t *hash; /* the md5 hash */
    uint64_t offset; /* the asset's offset in the file */
};

/* 
   parsed archive file header. 
   At the start of a state, assets are loaded. 
*/
struct archive_t {
    uint32_t assetCount;
    struct asset_t *assets;
};

struct archive_t *parseHeader(char *fileName);
void freeHeader(struct archive_t *archive);
#endif
