/*************************************************************************
    > File Name: test.c
    > name: Hu guanghui
    > number: 120L052208
    > Created Time: 2022年04月17日 星期日 16时21分35秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "BMP.h"
#include "Smooth.h"
int main(){
    printf("start main\n");
    BMP * newPict = bmpRead("../inputFile/pic.bmp");
    if (bmpWrite(newPict,"../outputFile/originPic.bmp")==0){
        printf("successfully write originPic\n");
    }
    BMP * smoothPic = smooth_basic(newPict);
    if (smoothPic!=NULL){
        if (bmpWrite(smoothPic,"../outputFile/smooth_basic.bmp")==0){
            printf("successfully write smooth_basic.bmp\n");
        }
    }
    printf("end main\n");
    return 0;
}