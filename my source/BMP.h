
#ifndef __BMP_H__
#define __BMP_H__
#include <stdint.h>
#include <stdio.h>
//位图文件头
#pragma pack(2)
typedef struct {
    uint16_t  bfType ;     //文件标志.固定为'BM',用来识别BMP位图类型
    uint32_t  bfSize ;	   //文件大小,占四个字节
    uint16_t  bfReserved1 ;//保留，总为0
    uint16_t  bfReserved2 ;//保留，总为0
    uint32_t  bfOffBits ;  //从文件开始到位图数据(bitmap data)开始之间的的偏移量
}FILEHEADER ;
//位图信息头
#pragma pack(2)
typedef struct {
    uint32_t biSize ;		   	//BITMAPINFOHEADER结构所需要的字数。
    uint32_t  biWidth ;		   	    //图象的宽度，以象素为单位 
    uint32_t  biHeight ;	   	    //图象的高度，以象素为单位 
    uint16_t  biPlanes ;	    //为目标设备说明位面数，其值将总是被设为1 
    uint16_t  biBitCount ;	   	//比特数/象素，其值为1、4、8、16、24、或32
    uint32_t biCompression ;  	//图象数据压缩的类型。其值可以是下述值之一：
	                              //BI_RGB：没有压缩；
	                              //BI_RLE8：每个象素8比特的RLE压缩编码，压缩格式由2字节组成(重复象素计数和颜色索引)；  
                                  //BI_RLE4：每个象素4比特的RLE压缩编码，压缩格式由2字节组成
  	                              //BI_BITFIELDS：每个象素的比特由指定的掩码决定。
    uint32_t biSizeImage ;		//图象的大小，以字节为单位。当用BI_RGB格式时，可设置为0  
    uint32_t biXPelsPerMeter ;	    //水平分辨率，用象素/米表示
    uint32_t biYPelsPerMeter ;	    //垂直分辨率，用象素/米表示
    uint32_t biClrUsed ;	  	//位图实际使用的彩色表中的颜色索引数
    uint32_t biClrImportant ; 	//对图象显示有重要影响的颜色索引的数目，如果是0，表示都重要。 
}INFOHEADER ;
//调色板
typedef struct  {
    uint8_t rgbBlue ;    //指定蓝色强度
    uint8_t rgbGreen ;	 //指定绿色强度 
    uint8_t rgbRed ;	 //指定红色强度 
    uint8_t rgbReserved ;//保留，设置为0 
}RGBQUAD ;
#pragma pack(1)
typedef struct {
	uint8_t red;
	uint8_t blue;
	uint8_t green;
	uint8_t nop;
}RBGINFO;
typedef struct {
	FILEHEADER *fileHead;
	INFOHEADER *infoHead;
	RGBQUAD *colorSet;
	RBGINFO *colorInfo;
}BMP;
RBGINFO* cell(BMP *pic,long i,long j);
BMP *bmpRead(const char *inPutName);
int bmpWrite(BMP* pic, char* outPutName);
BMP *newBMP();
/**
 * @brief Create a Space By Head object
 * 
 * @param pic 
 * @return int 
 */
int createSpaceByHead(BMP* pic);
void createHeadByPic(BMP *newPic, BMP *oldPic);
#endif
