#include <stdio.h>
#include <stdlib.h>
#include "archive.h"


struct archive_t *parseHeader(char *filename) {
    struct archive_t *archive;  
    FILE *fp;
    uint8_t headerBuffer[HEADER_SIZE]; /* just read the initial info buffer */
    uint8_t *buf; /* buffer for the actual file directory */
    uint32_t assetCount;
    uint32_t headerSize; /* size of header to read */
    
    archive = malloc(sizeof(struct archive_t));
    fp = fopen(filename, "rb");

    /* 
       read the asset count for the given archive
       This is a 2 byte int
     */
    fgets((char *) headerBuffer, HEADER_SIZE, (FILE *) fp);
    archive->assetCount =
        (headerBuffer[9] << 24) |
        (headerBuffer[8] << 16) |
        (headerBuffer[7] << 8)  |
        (headerBuffer[6]);

    
    archive->assets = malloc(sizeof(struct asset_t) * archive->assetCount);

    /* allocate enough space to read the rest of the header */
    headerSize = assetCount * (HASH_SIZE + ARCHIVE_PADDING + FILE_OFFSET)
    buf = malloc(sizeof(uint8_t) * headerSize);
    /* file pointer ought to already be incremented past the header. */
    fgets((char *) buf, headerSize, (FILE *) fp);

    for (uint16_t i = 0; i < assetCount; i+= ARCHIVE_PADDING) {
        uint32_t assetOffset = (i * (HASH_SIZE + ARCHIVE_PADDING + FILE_OFFSET));
        struct asset_t asset;
        
        asset.hash = malloc(sizeof(uint8_t) * 16);
        memcpy(asset.hash, buf + assetOffset, (size_t) 16);

        /* read the four bytes of the file offset. */
        asset.offset =
            (buf[assetOffset + 16] << 24)     |
            (buf[assetOffset + 16 + 1] << 16) |
            (buf[assetOffset + 16 + 2] << 8)  |
            (buf[assetOffset + 16 + 3]);

        archive->assets[i] = asset;
    }

    free(buf);
    
    return archive;
}

/* release the hefty resources reserved by the header. */
void freeHeader(struct archive_t *archive) {
    // TODO.
}
