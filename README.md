# pntr_assetsys

Load [pntr](https://github.com/RobLoach/pntr) assets from zip files with [assetsys](https://github.com/mattiasgustavsson/libs/blob/main/assetsys.h), a file system abstraction library.

## Example

``` c
#define PNTR_IMPLEMENTATION
#include "pntr.h"

#define PNTR_ASSETSYS_IMPLEMENTATION
#include "pntr_assetsys.h"

int main() {
    assetsys_t* sys = pntr_load_assetsys("resources.zip", "/res");
    pntr_image* logo = pntr_load_image_from_assetsys(sys, "/res/logo.png");

    // ...

    pntr_unload_image(logo);
    pntr_unload_assetsys(sys);

    return 0;
}
```

## API

``` c
assetsys_t* pntr_load_assetsys(char const* path, char const* mountAs);
assetsys_t* pntr_load_assetsys_from_memory(const void* data, size_t size, char const* mountAs);
bool pntr_assetsys_mount(assetsys_t* sys, const char* path, const char* mountAs);
void pntr_unload_assetsys(assetsys_t* sys);
unsigned char* pntr_load_file_from_assetsys(assetsys_t* sys, const char* path, unsigned int* bytesRead);
pntr_image* pntr_load_image_from_assetsys(assetsys_t* sys, const char* path);
pntr_font* pntr_load_font_bmf_from_assetsys(assetsys_t* sys, const char* path, const char* characters);
pntr_font* pntr_load_font_tty_from_assetsys(assetsys_t* sys, const char* path, int glyphWidth, int glyphHeight, const char* characters);
pntr_font* pntr_load_font_ttf_from_assetsys(assetsys_t* sys, const char* path, int fontSize);
pntr_sound* pntr_load_sound_from_assetsys(assetsys_t* sys, const char* path);
```

## License

* pntr_assetsys is [MIT](LICENSE) licensed
* [assetsys.h](https://github.com/mattiasgustavsson/libs/blob/main/assetsys.h) by [@mattiasgustavsson](https://github.com/mattiasgustavsson) is [MIT](https://github.com/mattiasgustavsson/libs/blob/main/assetsys.h#L6416) licensed
* [strpool.h](https://github.com/mattiasgustavsson/libs/blob/main/strpool.h) by [@mattiasgustavsson](https://github.com/mattiasgustavsson) is [MIT](https://github.com/mattiasgustavsson/libs/blob/main/strpool.h#L1260) licensed
