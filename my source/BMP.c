/*************************************************************************
    > File Name: BMP.c
    > name: Hu guanghui
    > number: 120L052208
    > Created Time: 2022年04月16日 星期六 21时00分49秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "BMP.h"
#include <string.h>
inline RBGINFO* cell(BMP *pic,long i,long j){
    return &(pic->colorInfo[(pic->infoHead->biWidth)*i+j]);
}
/**
 * @brief new a BMP only 4 pointer 
 * 
 * @return BMP* 
 */
BMP *newBMP(){
	BMP *pic =  (BMP*)malloc(sizeof(BMP));
	if (pic!=NULL){	
		pic->fileHead = (FILEHEADER*)malloc(sizeof(FILEHEADER));
		pic->infoHead = (INFOHEADER*)malloc(sizeof(INFOHEADER));
		pic->colorInfo = NULL;
		pic->colorSet = NULL;
		return pic;
	}
	else{
		return NULL;
	}
}
void createHeadByPic(BMP *newPic, BMP *oldPic){
	memcpy(newPic->fileHead,oldPic->fileHead,sizeof(FILEHEADER));
	memcpy(newPic->infoHead,oldPic->infoHead,sizeof(INFOHEADER));
}
int freeBMP(BMP* pic){
	if (pic==NULL) return 1;
	if ((pic->colorInfo!=NULL)&&(pic->infoHead)){
		size_t h = pic->infoHead->biHeight;
		size_t w = pic->infoHead->biWidth;
		for (size_t i = 0; i < h; i++){
			for (size_t j = 0; i < w; i++){
				free(cell(pic,i,j));
			}
		}
		free(pic->infoHead);
	}
	if (pic->colorSet!=NULL) free(pic->colorSet);
	if (pic->infoHead!=NULL) free(pic->infoHead);
	if (pic->fileHead!=NULL) free(pic->fileHead);
}
/**
 * @brief Create a Space By Head object
 * 
 * @param pic a not empty pic with not empty infohead
 * @return int 1:error;0:normal 
 */
int createSpaceByHead(BMP* pic){
	if ((pic==NULL)||(pic->infoHead==NULL)) return 1;
	pic->colorInfo = (RBGINFO*)malloc(sizeof(RBGINFO)*(pic->infoHead->biWidth)*(pic->infoHead->biHeight));
	if (pic->colorInfo!=NULL) return 1;
	else return 0;
}
BMP *bmpRead(const char *inPutName){
    FILE* fp;
	// printf("%s\n",inPutName);
	if ((fp=fopen(inPutName,"rb"))==NULL){
		printf("in if\n");
		printf("fail to open");
		return NULL;
	}
	int i,j;
	BMP *pic = (BMP*)malloc(sizeof(BMP));
	pic->fileHead = (FILEHEADER*)malloc(sizeof(FILEHEADER));
	pic->infoHead = (INFOHEADER*)malloc(sizeof(INFOHEADER));
	fread((void*)pic->fileHead,sizeof(FILEHEADER),1,fp);
	fread((void*)pic->infoHead,sizeof(INFOHEADER),1,fp);
	if (pic->infoHead->biBitCount==24) {
		pic->colorSet = NULL;
		long w = pic->infoHead->biWidth;
		long h = pic->infoHead->biHeight;
		if ((w<=0)||(h<=0)){
			printf("error size: height = %ld, weight = %ld\n",h,w);
			return NULL;
		}
		printf("picture size: height = %ld, weight = %ld\n",h,w);
    	int padding = (4 - ((w * 3) & 3)) & 3;
        pic->colorInfo = (RBGINFO*)malloc(sizeof(RBGINFO)*w*h);
		if (pic->colorInfo==NULL) {
			printf("too big!\n");
			return NULL;
		}
		for (i=0;i<h;i++){
			for (j=0;j<w;j++){
                cell(pic,i,j)->blue = fgetc(fp);
                cell(pic,i,j)->green = fgetc(fp);
                cell(pic,i,j)->red = fgetc(fp);
				fseek(fp,padding,SEEK_CUR);
			}
		}			
		fclose(fp);
		// printf("finish reading picture\n");
		return pic;
	}
	else {
        printf("not support this format:%d\n",pic->infoHead->biBitCount);
        return NULL;
    }
}
int bmpWrite(BMP* pic, char* outPutName){
    FILE* fp;
	// printf("%s\n",outPutName);
	if ((fp=fopen(outPutName,"wb"))==NULL){
		// printf("in write if\n");
		printf("fail to write\n");
		return 1;
	}
	// printf("can write open\n");
	if ((pic!=NULL)&&(pic->fileHead!=NULL)){
		fwrite(pic->fileHead,sizeof(FILEHEADER),1,fp);
		if (pic->infoHead!=NULL) fwrite(pic->infoHead,sizeof(INFOHEADER),1,fp);
		else {
			printf("infohead is empty\n");
			return 1;
		}
		if ((pic->infoHead->biBitCount==24)&&(pic->colorInfo!=NULL)){
			int w = pic->infoHead->biWidth;
			int h = pic->infoHead->biHeight;
			void* point = pic->colorInfo;
    		uint32_t padding = (4 - ((w * 3) & 3)) & 3;
			int empty = 0;
			for (int i=0; i<h; i++){
				for (int j=0; j<w; j++){
                	fputc(cell(pic,i,j)->blue,fp);
                	fputc(cell(pic,i,j)->green,fp);
                	fputc(cell(pic,i,j)->red,fp);
					fwrite(&empty,1,padding,fp);
				}
			}
		}
	}
	return 0;
}