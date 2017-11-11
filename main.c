#include <libgen.h>
#include <stdio.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define VTD_LOADER_IMPLEMENTATION
#include "vtd_loader.h"

const char *getFileExt(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename)
        return "";
    return dot + 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s image\n", argv[0]);
        return 1;
    }

    int texWidth, texHeight, texChannels;
    stbi_uc *pixels = stbi_load(argv[1], &texWidth, &texHeight, &texChannels, 0);

    if (!pixels) {
        fprintf(stderr, "Unable to load image %s\n", argv[1]);
        return 1;
    }

    VtdData image;

    image.width    = texWidth;
    image.height   = texHeight;
    image.channels = texChannels;

    size_t imageSize = texWidth * texHeight * texChannels * sizeof(uint8_t);;

    image.pixels = malloc(imageSize);

    memcpy(image.pixels, pixels, imageSize);

    stbi_image_free(pixels);

    char *filename = basename(argv[1]);
    const char *extLoc = getFileExt(filename);
    size_t nameLen = extLoc - filename;

    char vtdName[nameLen + 4];
    strncpy(vtdName, filename, nameLen - 1);
    strncpy(vtdName + nameLen - 1, ".vtd\0", 5);

    saveVtd(vtdName, &image);
}
