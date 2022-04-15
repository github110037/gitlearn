#include <stdio.h>
#include <stdlib.h>
#include "img_bmp.h"

void bmp_test(char* inPutName, char* outPutName)
{
	unsigned int* img, * img1, tmp1;
	int rows, cols, i, j;
	unsigned char* tmp;
	const int k = 1, b = 150;//k对比度 b亮度 

	printf("reading picture...\n");
	read_bmp(inPutName, &img, &rows, &cols);
	img1 = img;
	printf("reading successfully\n");
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
		{
			tmp = (unsigned char*)img;
			tmp1 = tmp[0] * k + b;
			tmp1 = tmp1 > 254 ? 255 : tmp1;
			tmp[0] = tmp1;
			tmp1 = tmp[1] * k + b;
			tmp1 = tmp1 > 254 ? 255 : tmp1;
			tmp[1] = tmp1;
			tmp1 = tmp[2] * k + b;
			tmp1 = tmp1 > 254 ? 255 : tmp1;
			tmp[2] = tmp1;
			img++;
		}
	printf("calculate finish\n");
	write_bmp(outPutName, img1, rows, cols);
	printf("successfully saved\n");
}

int main(int argc, char* argv[]) 
{
	bmp_test(argv[1],argv[2]);
	printf("generate a calculated picture named %s\n",argv[2]);
	for (int i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}
	return 0;
}