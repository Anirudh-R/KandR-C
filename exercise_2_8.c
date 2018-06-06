#include <stdio.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"

#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

unsigned int rightrot(unsigned int x, int n);

int main()
{
    unsigned int x, res;
    
    x = 0x50006272;
    
    printf("x: "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN"\n",
    BYTE_TO_BINARY(x>>24), BYTE_TO_BINARY(x>>16), BYTE_TO_BINARY(x>>8), BYTE_TO_BINARY(x));
    
    res = rightrot(x, 5);
    
    printf("r: "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN"\n",
    BYTE_TO_BINARY(res>>24), BYTE_TO_BINARY(res>>16), BYTE_TO_BINARY(res>>8), BYTE_TO_BINARY(res));
    
    return 0;
}

/* rightrot: Return x right rotated by n bits */
unsigned int rightrot(unsigned int x, int n)
{
    unsigned int N, lsb;
    
    N = 8*sizeof(unsigned int);
    
    while(x!=0 && n-- > 0)
    {
        lsb = x & 1;
        x = x >> 1;
        x = x | (lsb << (N-1));
    }
    
    return x;
}


