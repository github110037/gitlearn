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
    size_t j_record;
    size_t i_record;
    uint32_t cnt_i = 0;
    uint32_t cnt_j = 0;
    while (i<h-1){
        j = 0;
        i_record=i;
        while (j<w-1){
            cnt_i = 0;
            j_record = j;
            i=i_record;
            while ((cnt_i<T)&&(i<h-1)){
                cnt_j =0;
                j = j_record;
                while ((cnt_j<T)&&(j<w-1)) {
                    RBGINFO *newCell = cell(newPic,i,j);
                    newCell->blue = (cell(oldPic,i-1,j)->blue+cell(oldPic,i+1,j)->blue+cell(oldPic,i,j-1)->blue+cell(oldPic,i,j+1)->blue)>>2;
                    newCell->green = (cell(oldPic,i-1,j)->green+cell(oldPic,i+1,j)->green+cell(oldPic,i,j-1)->green+cell(oldPic,i,j+1)->green)>>2;
                    newCell->red = (cell(oldPic,i-1,j)->red+cell(oldPic,i+1,j)->red+cell(oldPic,i,j-1)->red+cell(oldPic,i,j+1)->red)>>2;
                    ++j;
                    ++cnt_j;
                }
                ++i;
                ++cnt_i;
            }
        }
    }
    return newPic;
}
