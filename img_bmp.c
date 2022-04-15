#include <stdio.h>
#include <stdlib.h>

// bmp图片头大小 24位深度的 
#define BMP_HEADER_SIZE 54

void read_bmp(const char* filename, unsigned int** img_data, int* height, int* width)
{
    FILE* fp;
    int i, j;

    printf("opening picture...\n");
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("fail to open bmp\n");
        exit(1);
    }
    printf("skip the fist 18 bytes...\n");
    for (i = 0; i < 18; i++) fgetc(fp);

    printf("reading the height and weight...\n");
    fread(width, sizeof(int), 1, fp);
    fread(height, sizeof(int), 1, fp);
    if ((*height) < 0 || (*width) < 0)
    {
        printf("do not support the height: %d, weight: %d\n", (*height), (*width));
        exit(1);
    }
    printf("the picture size: width = %d  height = %d \n", (*width), (*height));
    //unsigned int* temp = malloc((*height) * sizeof(unsigned int));
    *img_data = (unsigned int*)malloc((*width) * (*height) * sizeof(unsigned int));
    printf("skip the first 28 bytes...\n");
    for (i = 0; i < 28; i++) fgetc(fp);

    //每行必须有4的倍数 
    int padding = (4 - (((*width) * 3) & 3)) & 3;
    int idx = 0;

    printf("reading the each point...\n");
    for (i = 0; i < (*height); ++i)
    {
        for (j = 0; j < (*width); ++j)
        {
            unsigned char b = fgetc(fp); //B
            unsigned char g = fgetc(fp); //G
            unsigned char r = fgetc(fp); //R
            (*img_data)[idx] = (((unsigned int)r << 16) | ((unsigned int)g << 8) | ((unsigned int)b << 0));
            idx++;
        }
        //丢掉多余字节 
        for (j = 0; j < padding; ++j)
        {
            unsigned char b = fgetc(fp);
        }
    }
    printf("finish reading each point...\n");
    fclose(fp);
}


void write_bmp(const char* filename, unsigned int* img_data, int height, int width)
{
    FILE* fp;
    int i, j;
    unsigned int file_size = width * height * 3 + BMP_HEADER_SIZE;
    unsigned char header[BMP_HEADER_SIZE] = { 0x42, 0x4d,         // BMP & DIB
                                        0x00, 0x00, 0x00, 0x00,// size of file in bytes
                                        0x00, 0x00, 0x00, 0x00, // reserved
                                        0x36, 0x00, 0x00, 0x00, // offset of start of image data
                                        0x28, 0x00, 0x00, 0x00, // size of the DIB header
                                        0x00, 0x00, 0x00, 0x00,// width in pixels
                                        0x00, 0x00, 0x00, 0x00,// height in pixels
                                        0x01, 0x00, // number of color planes
                                        0x18, 0x00, // number of bits per pixel
                                        0x00, 0x00, 0x00, 0x00, // no compression - BI_RGB
                                        0x00, 0x00, 0x00, 0x00, // image size - dummy 0 for BI_RGB
                                        0x13, 0x0b, 0x00, 0x00, // horizontal ppm
                                        0x13, 0x0b, 0x00, 0x00, // vertical ppm
                                        0x00, 0x00, 0x00, 0x00, // default 2^n colors in palatte
                                        0x00, 0x00, 0x00, 0x00  // every color is important
    };
    #if 1
        header[2] = (file_size & 0xff);
        header[3] = ((file_size >> 8) & 0xff);
        header[4] = ((file_size >> 16) & 0xff);
        header[5] = ((file_size >> 24) & 0xff);
        header[18] = (width & 0xff);
        header[19] = ((width >> 8) & 0xff);
        header[20] = ((width >> 16) & 0xff);
        header[21] = ((width >> 24) & 0xff);
        header[22] = (height & 0xff);
        header[23] = ((height >> 8) & 0xff);
        header[24] = ((height >> 16) & 0xff);
        header[25] = ((height >> 24) & 0xff);
    #endif
    printf("write picture size: width = %d  height =  %d \n", width, height);
    if ((fp = fopen(filename, "wb")) == NULL)
    {
        printf("fail to write the file %s\n", filename);
        exit(1);
    }
    //写头 
    fwrite(header, 1, BMP_HEADER_SIZE, fp);
    //写像素点 
    int padding = (4 - ((width * 3) & 3)) & 3;
    int idx = 0;
    for (i = 0; i < height; ++i)
    {
        unsigned char p[3];
        for (j = 0; j < width; ++j)
        {
            //写像素点 
            p[0] = (img_data[idx] >> 0) & 0xff; //B
            p[1] = (img_data[idx] >> 8) & 0xff; //G
            p[2] = (img_data[idx] >> 16) & 0xff; //R
            idx++;
            fwrite(p, 1, 3, fp);
        }
        //写入多余字节 
        if (padding)
        {
            p[0] = p[1] = p[2] = 0;
            fwrite(p, 1, padding, fp);
        }
    }
    fclose(fp);
}
