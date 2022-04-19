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
#include <x86intrin.h>
uint64_t perf_counter(void)
{
    __asm__ __volatile__("" : : : "memory");
    uint64_t r =  __rdtsc();
    __asm__ __volatile__("" : : : "memory");

    return r;
}
int main(){
    printf("start main\n");
    uint64_t t0 = perf_counter();
    BMP * newPict = bmpRead("../inputFile/pic.bmp");
    uint64_t t1 = perf_counter();
    printf("reading clocks number is %ld\n", t1-t0);

    t0 = perf_counter();
    BMP *smoothPic = smooth_cache(newPict,127);
    t1 = perf_counter();
    printf("smooth_cache clocks number is %ld\n", t1-t0);

    t0 = perf_counter();
    smoothPic = smooth_basic(newPict);
    t1 = perf_counter();
    printf("smooth_basic clocks number is %ld\n", t1-t0);

    t0 = perf_counter();
    smoothPic = smooth_code(newPict);
    t1 = perf_counter();
    printf("smooth_code  clocks number is %ld\n", t1-t0);


    if (smoothPic!=NULL){
        if (bmpWrite(smoothPic,"../outputFile/smooth_basic.bmp")==0){
            printf("successfully write smooth_basic.bmp\n");
		}
    }
    freeBMP(newPict);
    freeBMP(smoothPic);
    printf("end main\n");
    return 0;
}
