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
#endif  // PNTR_ASSETSYS_ASSETSYS_H

/**
 * Load an asset file system, and mount the given path.
 *
 * @param path The path to either the folder, or .zip file to mount.
 * @param mountAs The desired mounted path, as an absolute path. For example: /res
 *
 * @return The \c assetsys_t, or \c NULL on failure.
 *
 * @see pntr_unload_assetsys()
 */
PNTR_ASSETSYS_API struct assetsys_t* pntr_load_assetsys(char const* path, char const* mountAs);

/**
 * Mount the given path to the given assetsys_t.
 *
 * @param sys The assetsys to mount the path to.
 * @param path The path to either the folder, or .zip file to mount.
 * @param mountAs The desired mounted path, as an absolute path. For example: /res
 *
 * @return \c true if the path was mounted successfully, \c false otherwise.
 */
PNTR_ASSETSYS_API bool pntr_assetsys_mount(struct assetsys_t* sys, const char* path, const char* mountAs);

/**
 * Load an asset .zip archive from data in memory, and mount the given path.
 *
 * @param data A pointer to an archive data buffer in memory.
 * @param size The size in bytes of the data buffer.
 * @param mountAs The desired mounted path, as an absolute path. For example: /res
 *
 * @return The \c assetsys_t, or \c NULL on failure.
 *
 * @see pntr_load_assetsys()
 */
PNTR_ASSETSYS_API struct assetsys_t* pntr_load_assetsys_from_memory(const void* data, size_t size, char const* mountAs);

/**
 * Unloads the given assetsys_t.
 *
 * @param sys The assetsys to unload.
 */
PNTR_ASSETSYS_API void pntr_unload_assetsys(struct assetsys_t* sys);

/**
 * Load a file from the given assetsys_t.
 *
 * @param sys The assetsys to load the file from.
 * @param path The path to the file to load.
 * @param bytesRead Output variable for the number of bytes read from the file.
 *
 * @return The file data, or \c NULL on failure.
 */
PNTR_ASSETSYS_API unsigned char* pntr_load_file_from_assetsys(struct assetsys_t* sys, const char* path, unsigned int* bytesRead);
PNTR_ASSETSYS_API const char* pntr_load_file_text_from_assetsys(struct assetsys_t* sys, const char* path);
PNTR_ASSETSYS_API pntr_image* pntr_load_image_from_assetsys(struct assetsys_t* sys, const char* path);
PNTR_ASSETSYS_API pntr_font* pntr_load_font_bmf_from_assetsys(struct assetsys_t* sys, const char* path, const char* characters);
PNTR_ASSETSYS_API pntr_font* pntr_load_font_tty_from_assetsys(struct assetsys_t* sys, const char* path, int glyphWidth, int glyphHeight, const char* characters);
PNTR_ASSETSYS_API pntr_font* pntr_load_font_ttf_from_assetsys(struct assetsys_t* sys, const char* path, int fontSize);

#ifdef PNTR_APP_API
PNTR_ASSETSYS_API pntr_sound* pntr_load_sound_from_assetsys(assetsys_t* sys, const char* path);
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
#define ASSETSYS_ASSERT(condition, message) ((void)0)
#define MINIZ_NO_TIME
#define MINIZ_NO_STDIO
#define MINIZ_NO_ARCHIVE_WRITING_APIS

// strpool
#define STRPOOL_MALLOC(ctx, size) (ASSETSYS_MALLOC(ctx, size))
#define STRPOOL_FREE(ctx, ptr) (ASSETSYS_FREE(ctx, ptr))
#define STRPOOL_IMPLEMENTATION
#define STRPOOL_ASSERT(condition, message) ((void)0)
#define STRPOOL_MEMSET(ptr, val, cnt) (PNTR_MEMSET(ptr, val, cnt))
#define STRPOOL_MEMCPY(dst, src, cnt) (PNTR_MEMCPY(dst, src, cnt))
//#define STRPOOL_MEMCMP( pr1, pr2, cnt ) ( my_memcmp_func( pr1, pr2, cnt ) )
//#define STRPOOL_STRNICMP( s1, s2, len ) ( my_strnicmp_func( s1, s2, len ) )

#ifndef PNTR_ASSETSYS_STRPOOL_H
#define PNTR_ASSETSYS_STRPOOL_H "libs/strpool.h"
#endif  // PNTR_ASSETSYS_STRPOOL_H
#include PNTR_ASSETSYS_STRPOOL_H

// assetsys
#define ASSETSYS_IMPLEMENTATION
#ifndef PNTR_ASSETSYS_ASSETSYS_H
#define PNTR_ASSETSYS_ASSETSYS_H "libs/assetsys.h"
#endif  // PNTR_ASSETSYS_ASSETSYS_H

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
        if (!pntr_assetsys_mount(sys, path, mountAs)) {
            assetsys_destroy(sys);
            return NULL;
        }
    }

    return sys;
}

PNTR_ASSETSYS_API bool pntr_assetsys_mount(assetsys_t* sys, const char* path, const char* mountAs) {
    if (sys == NULL || path == NULL || mountAs == NULL) {
        return false;
    }

    // Attempt to load the file through pntr, prefering using pntr_load_file().
    unsigned int bytesRead;
    unsigned char* data = pntr_load_file(path, &bytesRead);
    if (data != NULL) {
        assetsys_error_t result = assetsys_mount_from_memory(sys, data, bytesRead, mountAs);
        pntr_unload_file(data);
        return result;
    }

    return assetsys_mount(sys, path, mountAs) == ASSETSYS_SUCCESS;
}

PNTR_ASSETSYS_API assetsys_t* pntr_load_assetsys_from_memory(const void* data, size_t size, char const* mountAs) {
    assetsys_t* sys = assetsys_create(NULL);
    if (sys == NULL) {
        return NULL;
    }

    if (data != NULL && mountAs != NULL && size > 0) {
        if (assetsys_mount_from_memory(sys, data, size, mountAs) != ASSETSYS_SUCCESS) {
            assetsys_destroy(sys);
            return NULL;
        }
    }

    return sys;
}

PNTR_ASSETSYS_API void pntr_unload_assetsys(assetsys_t* sys) {
    if (sys == NULL) {
        return;
    }
    assetsys_destroy(sys);
}

PNTR_ASSETSYS_API unsigned char* pntr_load_file_from_assetsys(assetsys_t* sys, const char* path, unsigned int* bytesRead) {
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

PNTR_ASSETSYS_API const char* pntr_load_file_text_from_assetsys(assetsys_t* sys, const char* path) {
    unsigned int size;
    unsigned char* data = pntr_load_file_from_assetsys(sys, path, &size);
    if (data == NULL) {
        return NULL;
    }

    data[size] = '\0';
    return (const char*)data;
}

PNTR_ASSETSYS_API pntr_image* pntr_load_image_from_assetsys(assetsys_t* sys, const char* path) {
    unsigned int size;
    unsigned char* data = pntr_load_file_from_assetsys(sys, path, &size);
    if (data == NULL) {
        return NULL;
    }

    pntr_image* out = pntr_load_image_from_memory(pntr_get_file_image_type(path), data, size);
    PNTR_FREE(data);
    return out;
}

PNTR_ASSETSYS_API pntr_font* pntr_load_font_bmf_from_assetsys(assetsys_t* sys, const char* path, const char* characters) {
    unsigned int size;
    unsigned char* data = pntr_load_file_from_assetsys(sys, path, &size);
    if (data == NULL) {
        return NULL;
    }

    pntr_font* out = pntr_load_font_bmf_from_memory(data, size, characters);
    PNTR_FREE(data);
    return out;
}

PNTR_ASSETSYS_API pntr_font* pntr_load_font_tty_from_assetsys(assetsys_t* sys, const char* path, int glyphWidth, int glyphHeight, const char* characters) {
    unsigned int size;
    unsigned char* data = pntr_load_file_from_assetsys(sys, path, &size);
    if (data == NULL) {
        return NULL;
    }

    pntr_font* out = pntr_load_font_tty_from_memory(data, size, glyphWidth, glyphHeight, characters);
    PNTR_FREE(data);
    return out;
}

PNTR_ASSETSYS_API pntr_font* pntr_load_font_ttf_from_assetsys(assetsys_t* sys, const char* path, int fontSize) {
    unsigned int size;
    unsigned char* data = pntr_load_file_from_assetsys(sys, path, &size);
    if (data == NULL) {
        return NULL;
    }

    pntr_font* out = pntr_load_font_ttf_from_memory(data, size, fontSize);
    PNTR_FREE(data);
    return out;
}

#ifdef PNTR_APP_API
PNTR_ASSETSYS_API pntr_sound* pntr_load_sound_from_assetsys(assetsys_t* sys, const char* path) {
    unsigned int size;
    unsigned char* data = pntr_load_file_from_assetsys(sys, path, &size);
    if (data == NULL) {
        return NULL;
    }

    return pntr_load_sound_from_memory(pntr_app_get_file_sound_type(path), data, size);
}
#endif

#ifdef __cplusplus
}
#endif

#endif  // PNTR_ASSETSYS_IMPLEMENTATION_ONCE
#endif  // PNTR_ASSETSYS_IMPLEMENTATION
