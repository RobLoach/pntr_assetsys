#include <stdio.h>
#include <assert.h>

#define PNTR_DISABLE_MATH
#define PNTR_IMPLEMENTATION
#include "pntr.h"

#define PNTR_ASSETSYS_IMPLEMENTATION
#include "pntr_assetsys.h"

int main() {
    printf("pntr_load_assetsys()\n");
    {
        assetsys_t* sys = pntr_load_assetsys("resources", "/res");
        assert(sys != NULL);

        printf("pntr_load_file_from_assetsys()\n");
        unsigned int bytesRead;
        unsigned char* text = pntr_load_file_from_assetsys(sys, "/res/text.txt", &bytesRead);
        assert(text != NULL);
        assert(bytesRead > 5);
        assert(text[0] == 'H');
        assert(text[1] == 'e');

        printf("pntr_load_image_from_assetsys\n");
        pntr_image* logo = pntr_load_image_from_assetsys(sys, "/res/logo.png");
        assert(logo != NULL);

        pntr_unload_file(text);
        pntr_unload_image(logo);

        printf("pntr_unload_assetsys\n");
        pntr_unload_assetsys(sys);
    }

    printf("pntr_load_assetsys_from_memory()\n");
    {
        // Zip file with a test.txt file containing "Hello, World!"
        const unsigned char data[]  = {
            0x50, 0x4b, 0x03, 0x04, 0x0a, 0x03, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x9e, 0x23, 0x57, 0x84, 0x9e,
            0xe8, 0xb4, 0x0e, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x74, 0x65,
            0x73, 0x74, 0x2e, 0x74, 0x78, 0x74, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72,
            0x6c, 0x64, 0x21, 0x0a, 0x50, 0x4b, 0x01, 0x02, 0x3f, 0x03, 0x0a, 0x03, 0x00, 0x00, 0x00, 0x00,
            0xfc, 0x9e, 0x23, 0x57, 0x84, 0x9e, 0xe8, 0xb4, 0x0e, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,
            0x08, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x80, 0xb4, 0x81, 0x00, 0x00,
            0x00, 0x00, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74, 0x78, 0x74, 0x0a, 0x00, 0x20, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x0e, 0xf2, 0x2d, 0xc2, 0xde, 0xd9, 0x01, 0x00, 0x0e,
            0xf2, 0x2d, 0xc2, 0xde, 0xd9, 0x01, 0x00, 0x0e, 0xf2, 0x2d, 0xc2, 0xde, 0xd9, 0x01, 0x50, 0x4b,
            0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x5a, 0x00, 0x00, 0x00, 0x34, 0x00,
            0x00, 0x00, 0x00, 0x00
        };
        const size_t data_size = 164;

        // Load the memory as a .zip file
        assetsys_t* sys = pntr_load_assetsys_from_memory(data, data_size, "/res");
        assert(sys != NULL);

        unsigned int bytesRead;
        unsigned char* text = pntr_load_file_from_assetsys(sys, "/res/test.txt", &bytesRead);
        assert(text != NULL);
        assert(bytesRead > 5);
        assert(text[0] == 'H');
        assert(text[1] == 'e');

        pntr_unload_file(text);
        pntr_unload_assetsys(sys);
    }

    printf("pntr_assetsys_test: Tests passed");

    return 0;
}
