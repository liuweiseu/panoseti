// FITS test
//
// Note: FITS is lame.
// 80-col "cards"?  1-offset arrays?  gimme a break.
// Also the docs are lame; there are no complete examples

#include "fitsio.h"

void write_file(const char* name) {
    fitsfile *f;
    long dim[2] = {4,4};
    long fpixel[2]= {1,1};
    int status = 0;
    short data[16] = {1,2,3,4,5,6,7,8,8,7,6,5,4,3,2,1};

    fits_create_file(&f, name, &status);
    printf("status %d\n", status);
    fits_create_img(f, SHORT_IMG, 2, dim, &status);
    printf("status %d\n", status);
    fits_write_pix(f, TUSHORT, fpixel, 16, data, &status);
    printf("status %d\n", status);
    fits_close_file(f, &status);
    printf("status %d\n", status);
}

void read_file(const char* name) {
    fitsfile *f;
    int bitpix;
    int naxis;
    long dim[2];
    int status=0;
    short data[16];
    long fpixel[2]= {1,1};
    short nulval=0;

    fits_open_file(&f, name, READONLY, &status);
    printf("status %d\n", status);
    fits_get_img_param(f, 2, &bitpix, &naxis, dim, &status);
    printf("bitpix %d ndim %d dims %ld %ld\n", bitpix, naxis, dim[0], dim[1]);
    printf("status %d\n", status);
    fits_read_pix(f, TUSHORT, fpixel, 16, NULL, data, NULL, &status);
    printf("status %d\n", status);
    for (int i=0; i<16; i++) {
        printf("%d\n", data[i]);
    }
}

int main(int, char**) {
    write_file("!foo.fits");
    read_file("foo.fits");
}
