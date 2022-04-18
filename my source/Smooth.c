#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "BMP.h"
BMP *smooth_basic(BMP* oldPic){
    BMP *newPic = newBMP();
    newPic->fileHead = oldPic->fileHead;
    newPic->infoHead = oldPic->infoHead;
    newPic->colorSet = oldPic->colorSet;
    createSpaceByHead(newPic);
    for (size_t i = 1; i < newPic->infoHead->biHeight-1; i++){
        for (size_t j = 1; j < newPic->infoHead->biWidth-1; j++){
            cell(newPic,i,j)->blue = (cell(oldPic,i-1,j)->blue+cell(oldPic,i+1,j)->blue+cell(oldPic,i,j-1)->blue+cell(oldPic,i,j+1)->blue)/2;
            cell(newPic,i,j)->green = (cell(oldPic,i-1,j)->green+cell(oldPic,i+1,j)->green+cell(oldPic,i,j-1)->green+cell(oldPic,i,j+1)->green)/2;
            cell(newPic,i,j)->red = (cell(oldPic,i-1,j)->red+cell(oldPic,i+1,j)->red+cell(oldPic,i,j-1)->red+cell(oldPic,i,j+1)->red)/2;
        }
    }
    return newPic;
}
BMP *smooth_code(BMP* oldPic){
    BMP *newPic = newBMP();
    newPic->fileHead = oldPic->fileHead;
    newPic->infoHead = oldPic->infoHead;
    newPic->colorSet = oldPic->colorSet;
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