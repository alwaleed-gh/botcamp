#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1) //هنا استعملت الدايركتف هاذا عشان احشر البتات ورى بعض بدون بادنق
struct bmp_header {
    unsigned short type;
    unsigned int size;
    unsigned int reserved;
    unsigned int offset;
    unsigned int header_size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bpp;
};
#pragma pack(pop)

int main() {
    //هنا قاعد ادخل قيم بالفاريبال
    int w = 16, h = 16;
    struct bmp_header header = {0};
    header.type = 0x4D42;
    header.width = w;
    header.height = h;
    header.bpp = 24;
    header.offset = sizeof(struct bmp_header);
    header.size = header.offset + (w * h * 3);

    unsigned char cat_pattern[16][16] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
        {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
        {0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0},
        {0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0},
        {0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0},
        {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
        {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
        {0,0,1,1,0,0,1,1,1,0,0,1,1,1,0,0},
        {0,0,1,1,0,0,1,1,1,0,0,1,1,1,0,0},
        {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
        {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
        {0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    //هنا مرحلة الكتابه
    FILE *fh = fopen("cat_project.bmp", "wb");
    if (fh) {
        void *write_ptr = &header;
        fwrite(write_ptr, sizeof(struct bmp_header), 1, fh);

        unsigned char white[3] = {255, 255, 255}, black[3] = {0, 0, 0};

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (cat_pattern[i][j] == 1) fwrite(black, 3, 1, fh);
                else fwrite(white, 3, 1, fh);
            }
        }
        fclose(fh);
    }

    //هنا مرحلة القرائه
    fh = fopen("cat_project.bmp", "rb");
    if (fh) {
        void *raw_ptr = malloc(sizeof(struct bmp_header)); //حجز ذاكرة لمؤشر عام
        fread(raw_ptr, sizeof(struct bmp_header), 1, fh);

        struct bmp_header *sptr = (struct bmp_header *)raw_ptr;

        printf("Type: %x\nWidth: %d\nHeight: %d\n", sptr->type, sptr->width, sptr->height);

        fclose(fh);
        free(raw_ptr); 
    }

    return 0;
}
