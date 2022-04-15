#ifndef __IMG_BMP_H__
#define __IMG_BMP_H__

void read_bmp(const char* filename, unsigned int** img_data, int* height, int* width);
void write_bmp(const char* filename, unsigned int* img_data, int height, int width);

#endif
