
#ifndef __FILTERS_H__
#define __FILTERS_H__

#include <math.h>
#include "SDL.h"

typedef enum {
    FILTER_2XSAI      = 0,
    FILTER_SUPER2XSAI = 1,
    FILTER_SUPEREAGLE = 2,
    FILTER_ADVMAME2X  = 3,
    FILTER_TV2X       = 4,
    FILTER_NORMAL2X   = 5,
    FILTER_BILINEAR   = 6,
    FILTER_DOTMATRIX  = 7,
    FILTER_NUM        = 8
} t_filter;

typedef struct
{
    const char* name;
    t_filter type;
}
t_named_filter;


class CFilters
{
public:
    void filter_init_2xsai(Uint32);
    void filter_2xsai(Uint8*,Uint32,Uint8*,Uint32,int,int);
    void filter_super2xsai(Uint8*,Uint32,Uint8*,Uint32,int,int);
    void filter_supereagle(Uint8*,Uint32,Uint8*,Uint32,int,int);
    void filter_advmame2x(Uint8*,Uint32,Uint8*,Uint32,int,int);
    void filter_tv2x(Uint8*,Uint32,Uint8*,Uint32,int,int);
    void filter_normal2x(Uint8*,Uint32,Uint8*,Uint32,int,int);
    void filter_bilinear(Uint8*,Uint32,Uint8*,Uint32,int,int);
    void filter_dotmatrix(Uint8*,Uint32,Uint8*,Uint32,int,int);
    void filter_bicubic(Uint8*,Uint32,Uint8*,Uint32,int,int);
};



#endif
