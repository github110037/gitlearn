#ifndef __SMOOTH_H__
#define __SMOOTH_H__
#include "BMP.h"
BMP *smooth_basic(BMP* oldPic);
BMP *smooth_code(BMP* oldPic);
BMP *smooth_cache(BMP* oldPic,uint32_t T);
int freeBMP(BMP* pic);
#endif