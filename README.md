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
    pntr_image* logo = pntr_load_assetsys_image(sys, "/res/logo.png");

    // ...

    pntr_unload_image(logo);
    pntr_unload_assetsys(sys);

    return 0;
}
```

## API

``` c
assetsys_t* pntr_load_assetsys(char const* path, char const* mountAs);
void pntr_unload_assetsys(assetsys_t* sys);
unsigned char* pntr_load_assetsys_file(assetsys_t* sys, const char* path, unsigned int* bytesRead);
pntr_image* pntr_load_assetsys_image(assetsys_t* sys, const char* path);
pntr_font* pntr_load_assetsys_font_bmf(assetsys_t* sys, const char* path, const char* characters);
pntr_font* pntr_load_assetsys_font_tty(assetsys_t* sys, const char* path, int glyphWidth, int glyphHeight, const char* characters);
pntr_font* pntr_load_assetsys_font_ttf(assetsys_t* sys, const char* path, int fontSize);
pntr_sound* pntr_load_assetsys_sound(assetsys_t* sys, const char* path);
```

## License

MIT