/**********************************************************************************************
*
*   pntr_assetsys: Use assetsys, a file system abstraction, to read pntr assets from zip files.
*
*   Copyright 2023 Rob Loach (@RobLoach)
*
*   DEPENDENCIES:
*       pntr https://github.com/robloach/pntr
*       assetsys https://github.com/mattiasgustavsson/libs/blob/main/assetsys.h
*       strpool https://github.com/mattiasgustavsson/libs/blob/main/strpool.h
*
*   LICENSE: MIT
*
*       Copyright (c) 2023 Rob Loach (@RobLoach)
*
*       Permission is hereby granted, free of charge, to any person obtaining a copy of this
*       software and associated documentation files (the "Software"), to deal in the Software
*       without restriction, including without limitation the rights to use, copy, modify,
*       merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
*       permit persons to whom the Software is furnished to do so, subject to the following
*       conditions:

*       The above copyright notice and this permission notice shall be included in all copies
*       or substantial portions of the Software.

*       THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
*       INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
*       PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
*       HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
*       CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
*       OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
**********************************************************************************************/

#ifndef PNTR_ASSETSYS_H_
#define PNTR_ASSETSYS_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PNTR_ASSETSYS_API
    #define PNTR_ASSETSYS_API PNTR_API
#endif

#ifndef PNTR_ASSETSYS_ASSETSYS_H
#define PNTR_ASSETSYS_ASSETSYS_H "libs/assetsys.h"
#endif
#include PNTR_ASSETSYS_ASSETSYS_H

/**
 * Load an asset file system, and mount the given path.
 *
 * @param path The path to either the folder, or .zip file to mount.
 * @param mountAs The desired mounted path, as an absolute path. For example: /res
 *
 * @return The assetsys_t, or NULL on failure.
 *
 * @see pntr_unload_assetsys()
 */
PNTR_ASSETSYS_API assetsys_t* pntr_load_assetsys(char const* path, char const* mountAs);
PNTR_ASSETSYS_API void pntr_unload_assetsys(assetsys_t* sys);
PNTR_ASSETSYS_API unsigned char* pntr_load_assetsys_file(assetsys_t* sys, const char* path, unsigned int* bytesRead);
PNTR_ASSETSYS_API pntr_image* pntr_load_assetsys_image(assetsys_t* sys, const char* path);
PNTR_ASSETSYS_API pntr_font* pntr_load_assetsys_font_bmf(assetsys_t* sys, const char* path, const char* characters);
PNTR_ASSETSYS_API pntr_font* pntr_load_assetsys_font_tty(assetsys_t* sys, const char* path, int glyphWidth, int glyphHeight, const char* characters);
PNTR_ASSETSYS_API pntr_font* pntr_load_assetsys_font_ttf(assetsys_t* sys, const char* path, int fontSize);

#ifdef PNTR_APP_API
PNTR_ASSETSYS_API pntr_sound* pntr_load_assetsys_sound(assetsys_t* sys, const char* path);
#else
PNTR_ASSETSYS_API void* pntr_load_assetsys_sound(assetsys_t* sys, const char* path);
#endif

#ifdef __cplusplus
}
#endif

#endif  // PNTR_ASSETSYS_H_

#ifdef PNTR_ASSETSYS_IMPLEMENTATION
#ifndef PNTR_ASSETSYS_IMPLEMENTATION_ONCE
#define PNTR_ASSETSYS_IMPLEMENTATION_ONCE

// Dependency configuration
#define ASSETSYS_MALLOC(ctx, size) (PNTR_MALLOC(size))
#define ASSETSYS_FREE(ctx, ptr) (PNTR_FREE(ptr))
#define MINIZ_NO_TIME
#define MINIZ_NO_ARCHIVE_WRITING_APIS

// strpool
#define STRPOOL_MALLOC(ctx, size) (ASSETSYS_MALLOC(ctx, size))
#define STRPOOL_FREE(ctx, ptr) (ASSETSYS_FREE(ctx, ptr))
#define STRPOOL_IMPLEMENTATION
#ifndef PNTR_ASSETSYS_STRPOOL_H
#define PNTR_ASSETSYS_STRPOOL_H "libs/strpool.h"
#endif  // PNTR_ASSETSYS_STRPOOL_H
#include PNTR_ASSETSYS_STRPOOL_H

// assetsys
#define ASSETSYS_IMPLEMENTATION
#include PNTR_ASSETSYS_ASSETSYS_H

#ifdef __cplusplus
extern "C" {
#endif

PNTR_ASSETSYS_API assetsys_t* pntr_load_assetsys(char const* path, char const* mountAs) {
    assetsys_t* sys = assetsys_create(NULL);
    if (sys == NULL) {
        return NULL;
    }

    if (path != NULL && mountAs != NULL) {
        assetsys_mount(sys, path, mountAs);
    }

    return sys;
}

PNTR_ASSETSYS_API void pntr_unload_assetsys(assetsys_t* sys) {
    if (sys == NULL) {
        return;
    }
    assetsys_destroy(sys);
}

PNTR_ASSETSYS_API unsigned char* pntr_load_assetsys_file(assetsys_t* sys, const char* path, unsigned int* bytesRead) {
    if (sys == NULL || path == NULL) {
        return NULL;
    }

    // Load the file information from assetsys.
    assetsys_file_t file;
    if (assetsys_file(sys, path, &file) != 0) {
        return NULL;
    }

    // Find out the size of the file.
    int size = assetsys_file_size(sys, file);
    if (size <= 0) {
        return NULL;
    }

    // Create the memory buffer.
    unsigned char* out = PNTR_MALLOC(size + 1);
    if (out == NULL) {
        return NULL;
    }

    // Load the file into the buffer.
    int outSize = 0;
    if (assetsys_file_load(sys, file, &outSize, (void*)out, size) != 0) {
        PNTR_FREE(out);
        return NULL;
    }

    // Save how many bytes were read.
    if (bytesRead != NULL) {
        *bytesRead = outSize;
    }

    return out;
}

PNTR_ASSETSYS_API pntr_image* pntr_load_assetsys_image(assetsys_t* sys, const char* path) {
    unsigned int size;
    unsigned char* data = pntr_load_assetsys_file(sys, path, &size);
    if (data == NULL) {
        return NULL;
    }

    pntr_image* out = pntr_load_image_from_memory(data, size);
    PNTR_FREE(data);
    return out;
}

PNTR_ASSETSYS_API pntr_font* pntr_load_assetsys_font_bmf(assetsys_t* sys, const char* path, const char* characters) {
    unsigned int size;
    unsigned char* data = pntr_load_assetsys_file(sys, path, &size);
    if (data == NULL) {
        return NULL;
    }

    pntr_font* out = pntr_load_font_bmf_from_memory(data, size, characters);
    PNTR_FREE(data);
    return out;
}

PNTR_ASSETSYS_API pntr_font* pntr_load_assetsys_font_tty(assetsys_t* sys, const char* path, int glyphWidth, int glyphHeight, const char* characters) {
    unsigned int size;
    unsigned char* data = pntr_load_assetsys_file(sys, path, &size);
    if (data == NULL) {
        return NULL;
    }

    pntr_font* out = pntr_load_font_tty_from_memory(data, size, glyphWidth, glyphHeight, characters);
    PNTR_FREE(data);
    return out;
}

PNTR_ASSETSYS_API pntr_font* pntr_load_assetsys_font_ttf(assetsys_t* sys, const char* path, int fontSize) {
    unsigned int size;
    unsigned char* data = pntr_load_assetsys_file(sys, path, &size);
    if (data == NULL) {
        return NULL;
    }

    pntr_font* out = pntr_load_font_ttf_from_memory(data, size, fontSize);
    PNTR_FREE(data);
    return out;
}

#ifdef PNTR_APP_API
PNTR_ASSETSYS_API pntr_sound* pntr_load_assetsys_sound(assetsys_t* sys, const char* path) {
    unsigned int size;
    unsigned char* data = pntr_load_assetsys_file(sys, path, &size);
    if (data == NULL) {
        return NULL;
    }

    return pntr_load_sound_from_memory(path, data, size);
}
#else
PNTR_ASSETSYS_API void* pntr_load_assetsys_sound(assetsys_t* sys, const char* path) {
    (void)path;
    (void)sys;
    return NULL;
}
#endif

#ifdef __cplusplus
}
#endif

#endif  // PNTR_ASSETSYS_IMPLEMENTATION_ONCE
#endif  // PNTR_ASSETSYS_IMPLEMENTATION
