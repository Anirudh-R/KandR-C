#include <stdio.h>

/* The reason for the ugly temp name is that the */
/* MACRO won't work if x or y name is same as temp */
#define swap(t, x, y)       \
{                           \
    t temp;                 \
    temp = (x);             \   
    (x) = (y);              \ 
    (y) = temp;             \
}                           

int main(void)
{
    double x=2.9, y=-5.7;
    
    swap(double, x, y);
    
    printf("%f %f", x, y);
    
    return 0;
}
