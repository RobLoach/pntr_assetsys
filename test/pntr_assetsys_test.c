#include <stdio.h>
#include <assert.h>

#define PNTR_DISABLE_MATH
#define PNTR_IMPLEMENTATION
#include "pntr.h"

#define PNTR_ASSETSYS_IMPLEMENTATION
#include "pntr_assetsys.h"

int main() {
    printf("pntr_load_assetsys()\n");
    assetsys_t* sys = pntr_load_assetsys("resources", "/res");
    assert(sys != NULL);

    printf("pntr_load_assetsys_file()\n");
    unsigned int bytesRead;
    unsigned char* text = pntr_load_assetsys_file(sys, "/res/text.txt", &bytesRead);
    assert(bytesRead > 5);
    assert(text[0] == 'H');
    assert(text[1] == 'e');

    printf("pntr_load_assetsys_image\n");
    pntr_image* logo = pntr_load_assetsys_image(sys, "/res/logo.png");
    assert(logo != NULL);

    pntr_unload_file(text);
    pntr_unload_image(logo);


    printf("pntr_unload_assetsys\n");
    pntr_unload_assetsys(sys);

    return 0;
}
