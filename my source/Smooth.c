#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "BMP.h"
BMP *smooth_basic(BMP* oldPic){
    BMP *newPic = newBMP();
    createHeadByPic(newPic,oldPic);
    createSpaceByHead(newPic);
    for (size_t i = 1; i < newPic->infoHead->biHeight-1; i++){
        for (size_t j = 1; j < newPic->infoHead->biWidth-1; j++){
            cell(newPic,i,j)->blue = (cell(oldPic,i-1,j)->blue+cell(oldPic,i+1,j)->blue+cell(oldPic,i,j-1)->blue+cell(oldPic,i,j+1)->blue)/4;
            cell(newPic,i,j)->green = (cell(oldPic,i-1,j)->green+cell(oldPic,i+1,j)->green+cell(oldPic,i,j-1)->green+cell(oldPic,i,j+1)->green)/4;
            cell(newPic,i,j)->red = (cell(oldPic,i-1,j)->red+cell(oldPic,i+1,j)->red+cell(oldPic,i,j-1)->red+cell(oldPic,i,j+1)->red)/4;
        }
    }
    return newPic;
}
BMP *smooth_code(BMP* oldPic){
    BMP *newPic = newBMP();
    createHeadByPic(newPic,oldPic);
    createSpaceByHead(newPic);
    int w = newPic->infoHead->biWidth;
    int h = newPic->infoHead->biHeight;
    for (size_t i = 1; i < h-1; i++){
        for (size_t j = 1; j < w-1; j++){
            RBGINFO *newCell = cell(newPic,i,j);
            newCell->blue = (cell(oldPic,i-1,j)->blue+cell(oldPic,i+1,j)->blue+cell(oldPic,i,j-1)->blue+cell(oldPic,i,j+1)->blue)>>2;
            newCell->green = (cell(oldPic,i-1,j)->green+cell(oldPic,i+1,j)->green+cell(oldPic,i,j-1)->green+cell(oldPic,i,j+1)->green)>>2;
            newCell->red = (cell(oldPic,i-1,j)->red+cell(oldPic,i+1,j)->red+cell(oldPic,i,j-1)->red+cell(oldPic,i,j+1)->red)>>2;
        }
    }
    return newPic;
}
BMP *smooth_cache(BMP* oldPic,uint32_t T){
    BMP *newPic = newBMP();
    createHeadByPic(newPic,oldPic);
    createSpaceByHead(newPic);
    int w = newPic->infoHead->biWidth;
    int h = newPic->infoHead->biHeight;
    size_t i = 1;
    size_t j = 1;
    size_t j_start;
    size_t j_end;
    size_t i_start;
    size_t i_end;
    uint32_t cnt_i = 0;
    uint32_t cnt_j = 0;
    while (i<h-1){
        j = 0;
        i_start=i;
		size_t iend1 = i+T;
		size_t iend2 = h;
		i_end = (iend1<iend2) ? iend1 :iend2;
        while (j<w-1){
            i=i_start;
            j_start = j;
			size_t jend1 = j+T;
			size_t jend2 = w-1;
			j_end = (jend1<jend2) ? jend1 : jend2;
            while (i<i_end){
                j = j_start;
                while (j<j_end) {
                    RBGINFO *newCell = cell(newPic,i,j);
                    newCell->blue = (cell(oldPic,i-1,j)->blue+cell(oldPic,i+1,j)->blue+cell(oldPic,i,j-1)->blue+cell(oldPic,i,j+1)->blue)>>2;
                    newCell->green = (cell(oldPic,i-1,j)->green+cell(oldPic,i+1,j)->green+cell(oldPic,i,j-1)->green+cell(oldPic,i,j+1)->green)>>2;
                    newCell->red = (cell(oldPic,i-1,j)->red+cell(oldPic,i+1,j)->red+cell(oldPic,i,j-1)->red+cell(oldPic,i,j+1)->red)>>2;
                    ++j;
                }
                ++i;
            }
        }
    }
    return newPic;
}
